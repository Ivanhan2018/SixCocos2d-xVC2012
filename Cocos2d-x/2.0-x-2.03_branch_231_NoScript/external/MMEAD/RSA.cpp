#include "RSA.h"

// 生成密钥对
ERROR_INFO RSA::GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key)
{
	if (keyLen<MIN_KEYLEN_RSA || keyLen>MAX_KEYLEN_RSA)
		return ERROR_KEYLENGTH_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	keyLen/=2;

	time_t t;
	time(&t);
	irand((long)t);

    long seed[4];

	// 加快大素数生成
    gprime(15000);
	// IOBASE范围：2<=X<=256，通常取值10/16/256
	GetMIP()->IOBASE=16;
	// 随机
    for (int i=0;i<4;i++)
	{
		seed[i]=utility->RNDNUM(rand()/2,rand());
	}

	pKey->n=1;

	// 生成pq，并得到模数n=p*q
	pKey->p=StrongPrime(keyLen,seed[0],seed[1]);
	pKey->n*=pKey->p;
	pKey->q=StrongPrime(keyLen,seed[2],seed[3]);
    pKey->n*=pKey->q;
	// 计算密钥对长度
	pKey->keyLength = bits(pKey->n)/8;

#ifdef PRINT_RSA
	cout<<"p.isprime["<<prime(pKey->p)<<"]："<<pKey->p<<endl;
	cout<<"q.isprime["<<prime(pKey->q)<<"]："<<pKey->q<<endl;
	cout<<"n.isprime["<<prime(pKey->n)<<"]："<<pKey->n<<endl;
#endif

	// 计算欧拉t=(p-1)*(q-1)
	pKey->t=(pKey->p-1)*(pKey->q-1);

#ifdef PRINT_RSA
	cout<<"t.isprime["<<prime(pKey->t)<<"]："<<pKey->t<<endl;
#endif

	// 计算公钥(n,e)
	// 条件：e<t，且e和t互质
	// 常用：65537
	// ----------------------------------------------
	// 【指定较小的公钥因子可以提高密钥对的生成速度，
	// 但是容易遭受攻击，所以还是建议公钥因子用大数】
	// Cool.Cat@2013-02-22
	// ----------------------------------------------
	if (m_factor>0)
	{
		key->PubKey = m_factor;
	}
	else
	{
		// p由0/1生成，q由2/3生成，所以用0/3生成e
		key->PubKey = StrongPrime(keyLen,seed[0],seed[3]);
	}

	// e/t有可能不互质，尤其当factor由用户手动输入的情况下：）
	// 所以要验证e/t是否互质，如果不互质，则要重新生成e
	// 如果keyLen>1024，e的生成速度太慢，所以只尝试3次。
	// Cool.Cat@2013-02-22
	int retry = 0;
	while (gcd(key->PubKey,pKey->t)!=1)
	{
		seed[0]=utility->RNDNUM(rand()/2,rand());
		seed[1]=utility->RNDNUM(rand()/2,rand());
		key->PubKey = StrongPrime(keyLen,seed[0],seed[1]);
		retry++;
#ifdef PRINT_RSA
		for (int i=0;i<2;i++)
			cout<<"gcd.seed["<<i<<"]="<<seed[i]<<endl;
		cout<<"gcd.retry["<<retry<<"]"<<endl;
#endif
		if (retry>1)
			return ERROR_NOT_RELATIVELY_PRIME;
	}
	
#ifdef PRINT_RSA
	cout<<"e.isprime["<<prime(key->PubKey)<<"]："<<key->PubKey<<endl;
#endif

	// 计算私钥(n,d)=1/e mod t
	// 条件：d*e%t==1
	// xgcd(e,t,d,d,d)
	key->PriKey = inverse(key->PubKey,pKey->t);
#ifdef PRINT_RSA
	cout<<"d.isprime["<<prime(key->PriKey)<<"]："<<key->PriKey<<endl;
#endif

	return ERROR_NONE;
}

// 通过密钥对加密数据
ERROR_INFO RSA::EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	if (slen>(int)(pKey->keyLength))
		return ERROR_SOURCELENGTH_TOO_MUCH;

	// C=(M^e) mod n
	Big M = from_binary(slen,src);
	enc->m1 = pow(M,pKey->PubKey,pKey->n);

	return ERROR_NONE;
}

// 通过密钥对解密数据
ERROR_INFO RSA::DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	if (OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	// M=(C^d) mod n
	Big M = pow(enc->m1,pKey->PriKey,pKey->n);
	GetMIP()->IOBASE = OutIoBase;
	*dlen = cotstr(M.getbig(),dst);
	dst[*dlen] = 0;
	if (*dlen>(int)(pKey->keyLength))
		return ERROR_DESTLENGTH_TOO_MUCH;
	return ERROR_NONE;
}

// 签名
ERROR_INFO RSA::Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	if (OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	// 计算SHA
	Big hash;
	ERROR_INFO retv = Hash(&hash,src,slen,signLen);
	if (retv!=ERROR_NONE)
		return retv;

	char *tmp = new char[signLen/4];
	*dlen = to_binary(hash,signLen,tmp,FALSE);

	switch (OutIoBase)
	{
	case 16:
		{
			*dlen*=2;
			char *hexStr = new char[*dlen+1];
			memset(hexStr,0,sizeof(hexStr));
			for (int i=0;i<*dlen/2;i++)
				sprintf(hexStr,"%s%02X",hexStr,(unsigned char)tmp[i]);

			memcpy(dst,hexStr,*dlen);
			dst[*dlen] = 0;
			RP_ARRAY(hexStr);
			break;
		}
	case 256:
		{
			memcpy(dst,tmp,*dlen);
			dst[*dlen] = 0;
			break;
		}
	}

	RP_ARRAY(tmp);

	// 签名r=M^PriKey%n
	pKey->r = pow(hash,pKey->PriKey,pKey->n);

#ifdef PRINT_DSA
	cout<<"hash="<<hash<<endl;
	cout<<"r="<<pKey->r<<endl;
#endif

	return ERROR_NONE;
}

// 校验
ERROR_INFO RSA::Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase)
{
	if (InIoBase!=16 && InIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	Big hash;

	switch (InIoBase)
	{
	case 16:
		{
			slen/=2;
			char *binStr = new char[slen+1];
			for (int i=0;i<slen;i++)
			{
				binStr[i] = utility->s2n(src[i*2]) * 16 + utility->s2n(src[i*2+1]);
			}
			hash = from_binary(slen,binStr);
			RP_ARRAY(binStr);
			break;
		}
	case 256:
		{
			hash = from_binary(slen,src);
			break;
		}
	}

	// 计算M=r^PubKey%n
	Big M = pow(pKey->r,pKey->PubKey,pKey->n);
	if (M!=hash)
	{
#ifdef PRINT_DSA
	cout<<"hash="<<hash<<endl;
	cout<<"r="<<pKey->r<<endl;
	cout<<"M="<<M<<endl;
#endif
		return ERROR_DSA_VERIFY_NOMATCH;
	}

	return ERROR_NONE;
}

void RSA::Print(KEY_CONTEXT *key)
{
	KEY_CONTEXT_RSA *pKey = dynamic_cast<KEY_CONTEXT_RSA*>(key);
	if (!pKey)
		return;
	cout << "------------------------------------------" << endl;
	cout<<"PubKey.len["<<bits(pKey->PubKey)<<"].prime["<<prime(pKey->PubKey)<<"].isone["<<pKey->PubKey.isone()<<"].iszero["<<pKey->PubKey.iszero()<<"]"<<endl;
	cout<<"PriKey.len["<<bits(pKey->PriKey)<<"].prime["<<prime(pKey->PriKey)<<"].isone["<<pKey->PriKey.isone()<<"].iszero["<<pKey->PriKey.iszero()<<"]"<<endl;
	cout<<"P.len["<<bits(pKey->p)<<"].prime["<<prime(pKey->p)<<"].isone["<<pKey->p.isone()<<"].iszero["<<pKey->p.iszero()<<"]"<<endl;
	cout<<"Q.len["<<bits(pKey->q)<<"].prime["<<prime(pKey->q)<<"].isone["<<pKey->q.isone()<<"].iszero["<<pKey->q.iszero()<<"]"<<endl;
	cout<<"N.len["<<bits(pKey->n)<<"].prime["<<prime(pKey->n)<<"].isone["<<pKey->n.isone()<<"].iszero["<<pKey->n.iszero()<<"]"<<endl;
	cout<<"T.len["<<bits(pKey->t)<<"].prime["<<prime(pKey->t)<<"].isone["<<pKey->t.isone()<<"].iszero["<<pKey->t.iszero()<<"]"<<endl;
	cout << "------------------------------------------" << endl;
	cout<<"keyLength="<<this->GetKeyLength(key)<<endl;
}