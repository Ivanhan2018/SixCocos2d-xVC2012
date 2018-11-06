#include "ECC.h"

// 检查4a^3+27b^2≠0(mod p)，确保EC上不包含奇异点
ERROR_INFO ECC::CheckPowmod(Big n,Big p)
{
	Big r = n%p;
	if (r<0)
		r+=p;
	if (r==0)
		return ERROR_SINGULARITY_EXISTS;
	return ERROR_NONE;
}

ERROR_INFO ECC::CheckEqual(KEY_CONTEXT *key,Big x,Big y)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	Big left=pow(y,2,pKey->p);
	Big right=(pow(x,3)+pKey->a*x+pKey->b)%pKey->p;
	if (left!=right)
	{
#ifdef PRINT_ECC
		cout<<"left ="<<left<<endl;
		cout<<"right="<<right<<endl;
#endif
		return ERROR_NOT_INVALID_XY;
	}
	return ERROR_NONE;
}

// 生成EC=Ep(a,b)，并通过x/y选取G点
ERROR_INFO ECC::GenKeyToData(unsigned int keyLen,KEY_CONTEXT *key)
{
	if (keyLen!=160 && keyLen!=192 && keyLen!=256)
		return ERROR_KEYLENGTH_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	switch (keyLen)
	{
		// 20bytes
	case 160:
		{
			this->GetMIP()->IOBASE = 10;
			pKey->a = "-3";
			this->GetMIP()->IOBASE = 16;
			pKey->b = "1C97BEFC54BD7A8B65ACF89F81D4D4ADC565FA45";
			pKey->p = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF7FFFFFFF";
			pKey->n = "100000000000000000001F4C8F927AED3CA752257";
			pKey->x = "4A96B5688EF573284664698968C38BB913CBFC82";
			pKey->y = "23A628553168947D59DCC912042351377AC5FB32";
			break;
		}
		// 24bytes
	case 192:
		{
			this->GetMIP()->IOBASE = 10;
			pKey->a = "-3";
			this->GetMIP()->IOBASE = 16;
			pKey->b = "64210519E59C80E70FA7E9AB72243049FEB8DEECC146B9B1";
			pKey->p = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFEFFFFFFFFFFFFFFFF";
			pKey->n = "FFFFFFFFFFFFFFFFFFFFFFFF99DEF836146BC9B1B4D22831";
			pKey->x = "188da80eb03090f67cbf20eb43a18800f4ff0afd82ff1012";
			pKey->y = "07192b95ffc8da78631011ed6b24cdd573f977a11e794811";
			break;
		}
		// 32bytes
	case 256:
		{
			this->GetMIP()->IOBASE = 16;
			pKey->p = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFF";
			pKey->a = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFFFFFFFFFC";
			pKey->b = "28E9FA9E9D9F5E344D5A9E4BCF6509A7F39789F515AB8F92DDBCBD414D940E93";
			pKey->n = "FFFFFFFEFFFFFFFFFFFFFFFFFFFFFFFF7203DF6B21C6052B53BBF40939D54123";
			pKey->x = "32C4AE2C1F1981195F9904466A39C9948FE30BBFF2660BE1715A4589334C74C7";
			pKey->y = "BC3736A2F4F6779C59BDCEE36B692153D0A9877CC62A474002DF32E52139F0A0";
			break;
		}
	}

	// q必须为素数
	if (!prime(pKey->p))
		return ERROR_NOT_PRIME;

	// 检查是否存在奇异点
	ERROR_INFO result = CheckPowmod(4*pow(pKey->a,3)+27*pow(pKey->b,2),pKey->p);
	if (result!=ERROR_NONE)
		return result;

	// 初始化EC
	ecurve(pKey->a,pKey->b,pKey->p,MR_PROJECTIVE);

	// Point(x,y)不在EC上
	if (!pKey->G.set(pKey->x,pKey->y))
		return ERROR_NOT_IN_EC;

	pKey->W=pKey->G;
	pKey->W*=pKey->n;

	// Point(x,y)不是q的阶
	if (!pKey->W.iszero())
		return ERROR_NOT_ORDER_Q;

	// 私钥
	pKey->PriKey = rand(pKey->n);
	//pKey->PriKey = "16fdbb3f3e4d7d253c421ae5a09f1ce500d973c04ae91564";

	// 公钥
	ECn R = pKey->G;
	R*=pKey->PriKey;
	pKey->ep = R.get(pKey->PubKey);

	// 计算密钥对长度
	pKey->keyLength = bits(pKey->p)/8;

#ifdef PRINT_ECC
	cout<<"G="<<pKey->G<<endl;
	cout<<"PubKey.prime["<<prime(pKey->PubKey)<<"]="<<pKey->PubKey<<",ep="<<pKey->ep<<endl;
	cout<<"PriKey.prime["<<prime(pKey->PriKey)<<"]="<<pKey->PriKey<<endl;
#endif

	return ERROR_NONE;
}

// 通过密钥对加密数据
ERROR_INFO ECC::EncodeDataByKey(KEY_CONTEXT *key,char *src,int slen,ENCRYPT_CONTEXT *enc)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	ENCRYPT_CONTEXT_ECC *pEnc = dynamic_cast<ENCRYPT_CONTEXT_ECC*>(enc);
	if (!pEnc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

	if (slen>(int)(pKey->keyLength))
		return ERROR_SOURCELENGTH_TOO_MUCH;

	//GetMIP()->IOBASE = 10;

	// 生成随机数
	Big r = rand(pKey->n);

	// 将M映射到EC上的x坐标
	Big x = from_binary(slen,src);
	// 计算y坐标(y^2)(mod p)=(x^3+ax+b)(mod p)
	Big y = 0;

	this->GetMIP()->IOBASE=16;

	Big v = 0;

#ifdef PRINT_ECC
	UINT count = 0;
#endif
	while (1)
	{
		Big n = pow(x,3)+pKey->a*x+pKey->b;
		if (jacobi(n,pKey->p)!=1)
		{
			v+=1;
			x+=1;
#ifdef PRINT_ECC
			count++;
			cout<<"mapping M->Ep(a,b) ... count["<<count<<"]"<<endl;
			cout<<"x="<<x<<endl;
			cout<<"y="<<y<<endl;
			cout<<"v="<<v<<endl;
#endif
			continue;
		}
		
#ifdef PRINT_ECC
		cout<<"got X ..."<<endl;
#endif

		y = sqrt(n,pKey->p);
		// 如果可以取到平方根y
		if (!y.iszero())
		{
			// 再多验证一下，一定是恒等的。。。
			if (CheckEqual(pKey,x,y)==ERROR_NONE)
			{
#ifdef PRINT_ECC
				cout<<"got Y ..."<<endl;
#endif
				break;
			}
			else
			{
#ifdef PRINT_ECC
				cout<<"got Y ... But it's no equal!"<<endl;
#endif
			}
		}

#ifdef PRINT_ECC
		cout<<"got Y ... But it's no match!"<<endl;
#endif
	}

	ECn R;
	R.set(x,y);

	// save
	pEnc->v = v;

#ifdef PRINT_ECC
	// x=4A96B5688EF573284664698968C38BB913CBFC82
	// y=23A628553168947D59DCC912042351377AC5FB32
	cout<<"x="<<x<<endl;
	cout<<"y="<<y<<endl;
	cout<<"v="<<v<<endl;

	cout<<"x.OnCurve["<<is_on_curve(x)<<"]"<<endl;
#endif

#if 1
	// 加密
	ECn M;
	M.set(x);

	// 取公钥
	ECn PubKey = ECn(pKey->PubKey,pKey->ep);
	PubKey *= r;
	PubKey+=M;
	pEnc->m1 = PubKey;
#else
	// 加密
	// 取R点X坐标
	R.set(pKey->PubKey*r);
	R*=M_Final;

	R.get(pKey->m1);

	cout<<"pKey->PubKey*r="<<pKey->PubKey*r<<endl;
#endif

	// m2=rG
	pEnc->m2 = pKey->G;
	pEnc->m2 *= r;

#ifdef PRINT_ECC
	GetMIP()->IOBASE = 16;
	cout<<"m1="<<pKey->m1<<endl;
	cout<<"m2="<<pKey->m2<<endl;
#endif

	return ERROR_NONE;
}

// 通过密钥对解密数据
ERROR_INFO ECC::DecodeDataByKey(KEY_CONTEXT *key,ENCRYPT_CONTEXT *enc,char *dst,int *dlen,unsigned int OutIoBase)
{
	if (OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (!enc)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	ENCRYPT_CONTEXT_ECC *pEnc = dynamic_cast<ENCRYPT_CONTEXT_ECC*>(enc);
	if (!pEnc)
		return ERROR_ENC_CONTEXT_NOTEXISTS;

#if 1
	// 解密
	// result = M1 - PriKey*M2 = M + PubKey*r - PriKey*(G*r) = M + PubKey*r - PubKey*r = M
	ECn left = pEnc->m2;
	left *= pKey->PriKey;
	ECn retv = pEnc->m1;
	retv -= left;

	Big result = 0;
	retv.get(result);

	result -= pEnc->v;
#else
	// 解密
	// 取R点X坐标
	ECn R=pKey->m2;
	R *= pKey->PriKey;
	//R.set(pKey->PriKey*pKey->m2);
	//Big x=0;
	//R.get(x);
	// result = M1*(1/x) = M*x/x = M
	//Big result = pKey->m1/x;
	ECn retv = pKey->m1;
	retv = retv / pKey->m2;
	Big result = 0;
	retv.get(result);
#endif

#ifdef PRINT_ECC
	GetMIP()->IOBASE = 16;
	cout<<"m1="<<pKey->m1<<endl;
	cout<<"m2="<<pKey->m2<<endl;
	cout<<"result="<<result<<endl;
#endif

	GetMIP()->IOBASE = OutIoBase;
	*dlen = cotstr(result.getbig(),dst);
	dst[*dlen] = 0;
	if (*dlen>(int)(pKey->keyLength))
		return ERROR_DESTLENGTH_TOO_MUCH;
	return ERROR_NONE;
}

// 签名
ERROR_INFO ECC::Signature(KEY_CONTEXT *key,char *src,int slen,char *dst,int *dlen,unsigned int signLen,unsigned int OutIoBase)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (OutIoBase!=16 && OutIoBase!=256)
		return ERROR_IOBASE_INVALID;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
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

	// 取随机数k，1<=k<n
	// 每次签名k都必须随机生成
	Big k = rand(pKey->n);
	//Big k = "CADDC27FEFC3040C1CCA194542218E002F58D504A639B668";

	// 计算R(x,y)=kG
	ECn R = k*pKey->G;

	// 计算签名r=R.x
	// r=5C09A23549325C866F0C1D8D6AB81255977C90A9FD6D66C4
	R.get(pKey->r);
	pKey->r%=pKey->n;
	// 如果r==0，需要重新计算
	if (pKey->r==0)
		return ERROR_SIGN_R_ISZERO;

	// 计算k/q模逆
	// k=3A5DF42EDE377F21CA637377C20FE43EDAFF70F0332641E1
	k = inverse(k,pKey->n);

	// 计算签名s
	// s=C0DFFC8E4BA4A91EBFFBCE7FE07E202AAF567DC10D69D5E8
	pKey->s = (hash+pKey->PriKey*pKey->r)*k%pKey->n;

	// 如果s==0，需要重新计算
	if (pKey->s==0)
		return ERROR_SIGN_S_ISZERO;

#ifdef PRINT_ECDSA
	GetMIP()->IOBASE = 16;
	cout<<"PubKey.prime["<<prime(pKey->PubKey)<<"]="<<pKey->PubKey<<",ep="<<pKey->ep<<endl;
	cout<<"PriKey.prime["<<prime(pKey->PriKey)<<"]="<<pKey->PriKey<<endl;
	cout<<"r.prime["<<prime(pKey->r)<<"]="<<pKey->r<<endl;
	cout<<"s.prime["<<prime(pKey->s)<<"]="<<pKey->s<<endl;
	cout<<"hash["<<bits(hash)<<"]="<<hash<<endl;
#endif

	return ERROR_NONE;
}

// 校验
ERROR_INFO ECC::Verify(KEY_CONTEXT *key,char *src,int slen,unsigned int InIoBase)
{
	if (!key)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	if (InIoBase!=16 && InIoBase!=256)
		return ERROR_IOBASE_INVALID;

	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return ERROR_KEY_CONTEXT_NOTEXISTS;

	// 检查r/s，范围1<=r<n
	if (pKey->r>=pKey->n || pKey->s>=pKey->n || pKey->r<1 || pKey->s<1)
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
	
	// 取公钥
	ECn PubKey = ECn(pKey->PubKey,pKey->ep);

	// 计算模逆s=xgcd(s,n)
	Big s = inverse(pKey->s,pKey->n);

	Big u=hash*s%pKey->n;
	Big w=pKey->r*s%pKey->n;

	// 计算点Z=u2*PubKey+u1*G
	ECn Z = mul(w,PubKey,u,pKey->G);
	// 取Z点x坐标，得到v
	Big v;
	Z.get(v);
	v%=pKey->n;
	// 验证v和pKey->r是否一致
	if (v!=pKey->r)
	{
#ifdef PRINT_ECDSA
		GetMIP()->IOBASE = 16;
		cout<<"PubKey.prime["<<prime(pKey->PubKey)<<"]="<<pKey->PubKey<<",ep="<<pKey->ep<<endl;
		cout<<"PriKey.prime["<<prime(pKey->PriKey)<<"]="<<pKey->PriKey<<endl;
		cout<<"r.prime["<<prime(pKey->r)<<"]="<<pKey->r<<endl;
		cout<<"v.prime["<<prime(v)<<"]="<<v<<endl;
		cout<<"hash["<<bits(hash)<<"]="<<hash<<endl;
#endif
		return ERROR_VERIFY_VR_NOMATCH;
	}
	return ERROR_NONE;
}

void ECC::Print(KEY_CONTEXT *key)
{
	KEY_CONTEXT_ECC *pKey = dynamic_cast<KEY_CONTEXT_ECC*>(key);
	if (!pKey)
		return;
	cout << "------------------------------------------" << endl;
	cout<<"PubKey.len["<<bits(pKey->PubKey)<<"].prime["<<prime(pKey->PubKey)<<"].isone["<<pKey->PubKey.isone()<<"].iszero["<<pKey->PubKey.iszero()<<"]="<<pKey->PubKey<<endl;
	cout<<"PriKey.len["<<bits(pKey->PriKey)<<"].prime["<<prime(pKey->PriKey)<<"].isone["<<pKey->PriKey.isone()<<"].iszero["<<pKey->PriKey.iszero()<<"]="<<pKey->PriKey<<endl;
	cout<<"PubKey.OnCurve["<<is_on_curve(pKey->PubKey)<<"]"<<endl;
	cout<<"PriKey.OnCurve["<<is_on_curve(pKey->PriKey)<<"]"<<endl;
	cout << "------------------------------------------" << endl;
	cout<<"G="<<pKey->G<<endl;
	cout<<"W="<<pKey->W<<endl;
	cout<<"a="<<pKey->a<<".prime["<<prime(pKey->a)<<"]"<<endl;
	cout<<"b="<<pKey->b<<".prime["<<prime(pKey->b)<<"]"<<endl;
	cout<<"p="<<pKey->p<<".prime["<<prime(pKey->p)<<"]"<<endl;
	cout<<"n="<<pKey->n<<".prime["<<prime(pKey->n)<<"]"<<endl;
	cout<<"x="<<pKey->x<<".prime["<<prime(pKey->x)<<"]"<<endl;
	cout<<"y="<<pKey->y<<".prime["<<prime(pKey->y)<<"]"<<endl;
	cout << "------------------------------------------" << endl;

	Big x,y,z;
	pKey->G.getxyz(x,y,z);
	cout<<"G.XYZ={"<<x<<",Y="<<y<<",Z="<<z<<"}.prime{"<<prime(x)<<","<<prime(y)<<","<<prime(z)<<"}"<<endl;
	pKey->W.getxyz(x,y,z);
	cout<<"W.XYZ={"<<x<<",Y="<<y<<",Z="<<z<<"}.prime{"<<prime(x)<<","<<prime(y)<<","<<prime(z)<<"}"<<endl;

	cout<<"keyLength="<<this->GetKeyLength(key)<<endl;
}