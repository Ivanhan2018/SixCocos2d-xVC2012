#include "ElGamal.h"

// 生成EC=Ep(a,b)，并通过x/y选取G点
ERROR_INFO ElGamal::GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key)
{
	// p范围应在[512,1024]之间
	if (keyLen<MIN_KEYLEN_ELGAMAL || keyLen>MAX_KEYLEN_ELGAMAL)
		return ERROR_EL_BITS_P_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	time_t t;
	time(&t);
	irand((long)t);

	long seed[2];

	// 加快大素数生成
    gprime(15000);
	// IOBASE范围：2<=X<=256，通常取值10/16/256
	GetMIP()->IOBASE=16;

	// 随机
    for (int i=0;i<2;i++)
	{
		seed[i]=utility->RNDNUM(rand()/2,rand());
	}

	// 生成p
#ifdef TEST_SHORT_PRIME
	pKey->p = P;
#else
	pKey->p=StrongPrime(keyLen,seed[0],seed[1]);
#endif

	// p必须为素数
	if (!prime(pKey->p))
		return ERROR_NOT_PRIME;

	// 生成私钥
#ifdef TEST_SHORT_PRIME
	pKey->PriKey = PK;
#else
	while(pKey->PriKey==0)
		pKey->PriKey = rand(pKey->p-1);
#endif

	// 生成g
#ifdef TEST_SHORT_PRIME
	pKey->g = G;
#else
	while(pKey->g==0)
		pKey->g = rand(pKey->p-1);
#endif

#ifdef PRINT_ELGAMAL
	//cout<<"egcd="<<gcd(pKey->q,pKey->g)<<endl;
	//cout<<"xgcd="<<inverse(pKey->q,pKey->g)<<endl;
#endif

	// 生成公钥(PubKey,g,p)
	pKey->PubKey = pow(pKey->g,pKey->PriKey,pKey->p);

	// 计算密钥对长度
	pKey->keyLength = bits(pKey->p)/8;

	return ERROR_NONE;
}

// 通过密钥对加密数据
ERROR_INFO ElGamal::EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	if (slen>=(int)(pKey->keyLength))
		return ERROR_SOURCELENGTH_TOO_MUCH;

	Big M = from_binary(slen,src);

	// 生成随机k，且k/p-1互质
	Big k;
    do
    {
		k=rand(pKey->p-1);
    } while (gcd(pKey->p-1,k)!=1);

	// 计算a=g^k(mod p)
	enc->m1 = pow(pKey->g,k,pKey->p);

	// 计算b=y^kM(mod p)
	enc->m2 = modmult(pow(pKey->PubKey,k,pKey->p),M,pKey->p);

	return ERROR_NONE;
}

// 通过密钥对解密数据
ERROR_INFO ElGamal::DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	if (OutIoBase!=10 && OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	// 计算M
	Big M = modmult(enc->m2,pow(enc->m1,pKey->p-1-pKey->PriKey,pKey->p),pKey->p);

	GetMIP()->IOBASE = OutIoBase;

	*dlen = cotstr(M.getbig(),dst);
	dst[*dlen] = 0;
	if (*dlen>=(int)(pKey->keyLength))
		return ERROR_DESTLENGTH_TOO_MUCH;
	return ERROR_NONE;
}

// 签名
ERROR_INFO ElGamal::Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	if (OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
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

	// 生成随机k，且k/p-1互质
	Big k;
#ifdef TEST_SHORT_PRIME
	k=K;
#else
    do
    {
		k=rand(pKey->p-1);
    } while (gcd(pKey->p-1,k)!=1);
#endif

	// 保证：hash < (p-1)
	hash %= (pKey->p-1);

	// 计算r=g^k(mod p)
	pKey->r = pow(pKey->g,k,pKey->p);

	if (pKey->r<=0)
		return ERROR_SIGN_R_ISZERO;

	// 计算k/p-1模逆ik=inverse(k,p-1)
	Big ik = inverse(k,pKey->p-1);

	// 计算temp=hash-xr
	Big temp = hash-pKey->PriKey*pKey->r;

	// 计算s=(ik*temp)(mod p-1)
	pKey->s = modmult(ik,temp,pKey->p-1);

	// 防止s出现负数
	pKey->s += (pKey->p-1);

	if (pKey->s<=0)
		return ERROR_SIGN_S_ISZERO;

#ifdef PRINT_ELGAMAL
	GetMIP()->IOBASE = 16;
	cout<<"r.prime["<<prime(pKey->r)<<"]="<<pKey->r<<endl;
	cout<<"s.prime["<<prime(pKey->s)<<"]="<<pKey->s<<endl;
	cout<<"hash["<<bits(hash)<<"]="<<hash<<endl;
#endif

	return ERROR_NONE;
}

// 校验
ERROR_INFO ElGamal::Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (InIoBase!=16 && InIoBase!=256)
		return ERROR_IOBASE_INVALID;

	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	// 检查0<r<p，且0<s<p-1
	if (pKey->r>=pKey->p || pKey->s>=pKey->p-1 || pKey->r<1 || pKey->s<1)
		return ERROR_VERIFY_RSP_NORELATIVELYPRIME;

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

	// 保证：hash < (p-1)
	hash %= (pKey->p-1);

	// v = (g^r*r^s) mod p
	Big v = modmult(pow(pKey->PubKey,pKey->r,pKey->p),pow(pKey->r,pKey->s,pKey->p),pKey->p);
	//Big v = pow(pKey->PubKey,pKey->r,pKey->r,pKey->s,pKey->p);

	// x = (g^hash) mod p
	Big x = pow(pKey->g,hash,pKey->p);

#ifdef PRINT_ELGAMAL
	GetMIP()->IOBASE = 16;
	cout<<"r.prime["<<prime(pKey->r)<<"]="<<pKey->r<<endl;
	cout<<"v.prime["<<prime(v)<<"]="<<v<<endl;
	cout<<"x.prime["<<prime(x)<<"]="<<x<<endl;
	cout<<"hash["<<bits(hash)<<"]="<<hash<<endl;
#endif

	// 验证：(y^r*r^s) mod p = (g^hash) mod p
	if (v!=x)
		return ERROR_VERIFY_VR_NOMATCH;
	return ERROR_NONE;
}

void ElGamal::Print(KEY_CONTEXT *key)
{
	KEY_CONTEXT_ELGAMAL *pKey = dynamic_cast<KEY_CONTEXT_ELGAMAL*>(key);
	if (!pKey)
		return;

	GetMIP()->IOBASE = 10;
	cout << "------------------------------------------" << endl;
	cout<<"PubKey.len["<<bits(pKey->PubKey)<<"].prime["<<prime(pKey->PubKey)<<"].isone["<<pKey->PubKey.isone()<<"].iszero["<<pKey->PubKey.iszero()<<"]="<<pKey->PubKey<<endl;
	cout<<"PriKey.len["<<bits(pKey->PriKey)<<"].prime["<<prime(pKey->PriKey)<<"].isone["<<pKey->PriKey.isone()<<"].iszero["<<pKey->PriKey.iszero()<<"]="<<pKey->PriKey<<endl;
	cout<<"P.len["<<bits(pKey->p)<<"].prime["<<prime(pKey->p)<<"].isone["<<pKey->p.isone()<<"].iszero["<<pKey->p.iszero()<<"]="<<pKey->p<<endl;
	//cout<<"Q.len["<<bits(pKey->q)<<"].prime["<<prime(pKey->q)<<"].isone["<<pKey->q.isone()<<"].iszero["<<pKey->q.iszero()<<"]="<<pKey->q<<endl;
	cout<<"G.len["<<bits(pKey->g)<<"].prime["<<prime(pKey->g)<<"].isone["<<pKey->g.isone()<<"].iszero["<<pKey->g.iszero()<<"]="<<pKey->g<<endl;
	cout<<"R.len["<<bits(pKey->r)<<"].prime["<<prime(pKey->r)<<"].isone["<<pKey->r.isone()<<"].iszero["<<pKey->r.iszero()<<"]="<<pKey->r<<endl;
	cout<<"S.len["<<bits(pKey->s)<<"].prime["<<prime(pKey->s)<<"].isone["<<pKey->s.isone()<<"].iszero["<<pKey->s.iszero()<<"]="<<pKey->s<<endl;
	cout << "------------------------------------------" << endl;
	cout<<"keyLength="<<this->GetKeyLength(key)<<endl;
}