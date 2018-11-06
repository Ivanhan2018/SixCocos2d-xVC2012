#include "TDEA.h"

TDEA::TDEA()
{
	memset(enKnL,0,sizeof(enKnL));
	memset(deKnL,0,sizeof(deKnL));
	memset(enKnR,0,sizeof(enKnR));
	memset(deKnR,0,sizeof(deKnR));
	memset(enKn3,0,sizeof(enKn3));
	memset(deKn3,0,sizeof(deKn3));
}

TDEA::~TDEA()
{
}

void TDEA::Padding(unsigned char *src,unsigned int slen,unsigned char *dst,unsigned int dlen)
{
	if (!src || !dst)
		return;

	if (slen<dlen)
	{
		unsigned int count = (unsigned int)(dlen/slen);
		unsigned int left = dlen-count*slen;
		// copy whole src
		for (unsigned int i=0;i<count;i++)
			for (unsigned int j=0;j<slen;j++)
				dst[i*slen+j] = src[i*slen+j];
		// padding left part
		for (unsigned int i=0;i<left;i++)
			dst[count*slen+i] = src[i];
	}
	else if (slen>=dlen)
	{
		// copy a part of src
		for (unsigned int i=0;i<dlen;i++)
			dst[i] = src[i];
	}
	dst[dlen] = 0;
}

// 设置密钥
void TDEA::deskey(unsigned char *pKey,bool bEncode,ED_TYPE uType)
{
	unsigned char pc1m[56] = {0};
	unsigned char pcr[56] = {0};
	unsigned long long kn[32] = {0};

	for (int j=0;j<56;j++)
	{
		int l = pc1[j];
		int m = l & 07;
		// 最多只取pKey的前8个字节，即传入的pKey不得低于8字节
		// Cool.Cat
		pc1m[j] = (pKey[l>>3]&bytebit[m])?1:0;
	}

	for(int i=0;i<16;i++)
	{
		int n=0;
		int m=0;

		// 加密
		if(bEncode)
			m = i << 1;
		else 
			m = (15 - i) << 1;

		n = m + 1;
		kn[m] = kn[n] = 0L;

		for(int j = 0; j < 28; j++ ) 
		{
			int l = j + totrot[i];
			if( l < 28 ) 
				pcr[j] = pc1m[l];
			else 
				pcr[j] = pc1m[l - 28];
		}

		for(int j = 28; j < 56; j++ ) 
		{
			int l = j + totrot[i];
			if( l < 56 ) 
				pcr[j] = pc1m[l];
			else 
				pcr[j] = pc1m[l - 28];
		}

		for(int j = 0; j < 24; j++ ) 
		{
			if( pcr[pc2[j]] ) 
				kn[m] |= bigbyte[j];
			if( pcr[pc2[j+24]] ) 
				kn[n] |= bigbyte[j];
		}
	}
	cookey(kn,bEncode,uType);
}

void TDEA::cookey(unsigned long long *raw1,bool bEncode,ED_TYPE uType)
{
	unsigned long long *cook, *raw0 = 0;
	unsigned long long dough[32] = {0};

	cook = dough;
	for(int i = 0; i < 16; i++, raw1++ ) 
	{
		raw0 = raw1++;
		*cook	 = (*raw0 & 0x00fc0000L) << 6;
		*cook	|= (*raw0 & 0x00000fc0L) << 10;
		*cook	|= (*raw1 & 0x00fc0000L) >> 10;
		*cook++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cook	 = (*raw0 & 0x0003f000L) << 12;
		*cook	|= (*raw0 & 0x0000003fL) << 16;
		*cook	|= (*raw1 & 0x0003f000L) >> 4;
		*cook++ |= (*raw1 & 0x0000003fL);
	}
	usekey(dough,bEncode,uType);
}

void TDEA::cpkey(unsigned long long *into,bool bEncode,ED_TYPE uType)
{
	unsigned long long *from, *endp;

	if (bEncode)
	{
		from = enKnL[uType], endp = &enKnL[uType][32];
	}
	else
	{
		from = deKnL[uType], endp = &deKnL[uType][32];
	}
	while( from < endp ) 
		*into++ = *from++;
}

void TDEA::usekey(unsigned long long *from,bool bEncode,ED_TYPE uType)
{
	unsigned long long *to, *endp = 0;

	if (bEncode)
	{
		to = enKnL[uType], endp = &enKnL[uType][32];
	}
	else
	{
		to = deKnL[uType], endp = &deKnL[uType][32];
	}
	while( to < endp )
		*to++ = *from++;
}

void TDEA::scrunch(unsigned char *outof,unsigned long long *into)
{
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into	 = (*outof++ & 0xffL) << 24;
	*into	|= (*outof++ & 0xffL) << 16;
	*into	|= (*outof++ & 0xffL) << 8;
	*into	|= (*outof   & 0xffL);
}

void TDEA::unscrun(unsigned long long *outof,unsigned char *into)
{
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into++ =  *outof++	 & 0xffL;
	*into++ = (*outof >> 24) & 0xffL;
	*into++ = (*outof >> 16) & 0xffL;
	*into++ = (*outof >>  8) & 0xffL;
	*into	=  *outof	 & 0xffL;
}

void TDEA::desfunc(unsigned long long *block,unsigned long long *keys)
{
	unsigned long long fval, work, right, leftt = 0;
	int round = 0;

	leftt = block[0];
	right = block[1];
	work = ((leftt >> 4) ^ right) & 0x0f0f0f0fL;
	right ^= work;
	leftt ^= (work << 4);
	work = ((leftt >> 16) ^ right) & 0x0000ffffL;
	right ^= work;
	leftt ^= (work << 16);
	work = ((right >> 2) ^ leftt) & 0x33333333L;
	leftt ^= work;
	right ^= (work << 2);
	work = ((right >> 8) ^ leftt) & 0x00ff00ffL;
	leftt ^= work;
	right ^= (work << 8);
	right = ((right << 1) | ((right >> 31) & 1L)) & 0xffffffffL;
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = ((leftt << 1) | ((leftt >> 31) & 1L)) & 0xffffffffL;

	for( round = 0; round < 8; round++ ) 
	{
		work  = (right << 28) | (right >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = right ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		leftt ^= fval;
		work  = (leftt << 28) | (leftt >> 4);
		work ^= *keys++;
		fval  = SP7[ work		 & 0x3fL];
		fval |= SP5[(work >>  8) & 0x3fL];
		fval |= SP3[(work >> 16) & 0x3fL];
		fval |= SP1[(work >> 24) & 0x3fL];
		work  = leftt ^ *keys++;
		fval |= SP8[ work		 & 0x3fL];
		fval |= SP6[(work >>  8) & 0x3fL];
		fval |= SP4[(work >> 16) & 0x3fL];
		fval |= SP2[(work >> 24) & 0x3fL];
		right ^= fval;
	}

	right = (right << 31) | (right >> 1);
	work = (leftt ^ right) & 0xaaaaaaaaL;
	leftt ^= work;
	right ^= work;
	leftt = (leftt << 31) | (leftt >> 1);
	work = ((leftt >> 8) ^ right) & 0x00ff00ffL;
	right ^= work;
	leftt ^= (work << 8);
	work = ((leftt >> 2) ^ right) & 0x33333333L;
	right ^= work;
	leftt ^= (work << 2);
	work = ((right >> 16) ^ leftt) & 0x0000ffffL;
	leftt ^= work;
	right ^= (work << 16);
	work = ((right >> 4) ^ leftt) & 0x0f0f0f0fL;
	leftt ^= work;
	right ^= (work << 4);
	*block++ = right;
	*block = leftt;
}

void TDEA::InitKeySingle(unsigned char *pKey,unsigned int kLen)
{
	// 密钥有可能不是8字节，所以这里要特殊处理下
	// Cool.Cat
	unsigned char *newKey = new unsigned char[9];
	memset(newKey,0,sizeof(newKey));
	this->Padding(pKey,kLen,newKey,8);

#ifdef DEBUG_KEY
	printf("InitKeySingle.pKey[%s].newKey[%s]\n",pKey,newKey);
#endif

	// -------------------------
	// MODE_E1 => enKnL => deKnL
	// -------------------------
	// enKnL->en
	deskey(newKey,true,TYPE_SINGLE);
	// deKnL->de
	deskey(newKey,false,TYPE_SINGLE);

	delete [] newKey;
	newKey = 0;
}

void TDEA::InitKeyDouble(unsigned char *pKey,unsigned int kLen)
{
	// 密钥有可能不是16字节，所以这里要特殊处理下
	// Cool.Cat
	unsigned char *newKey = new unsigned char[17];
	memset(newKey,0,sizeof(newKey));
	this->Padding(pKey,kLen,newKey,16);

#ifdef DEBUG_KEY
	printf("InitKeyDouble.pKey[%s].newKey[%s]\n",pKey,newKey);
#endif

	// --------------------------------------
	// MODE_ED2 => enKnR/deKn3 => enKn3/deKnR
	// --------------------------------------
	// deKnR->de
	deskey(&newKey[8],false,TYPE_DOUBLE);
	cpkey(deKnR[TYPE_DOUBLE],false,TYPE_DOUBLE);
	// enKn3->en
	deskey(newKey,true,TYPE_DOUBLE);
	cpkey(enKn3[TYPE_DOUBLE],true,TYPE_DOUBLE);
	// ----------------------
	// enKnR->en
	deskey(&newKey[8],true,TYPE_DOUBLE);
	cpkey(enKnR[TYPE_DOUBLE],true,TYPE_DOUBLE);
	// deKn3->de
	deskey(newKey,false,TYPE_DOUBLE);
	cpkey(deKn3[TYPE_DOUBLE],false,TYPE_DOUBLE);

	delete [] newKey;
	newKey = 0;
}

void TDEA::InitKeyTriple(unsigned char *pKey,unsigned int kLen)
{
	// 密钥有可能不是24字节，所以这里要特殊处理下
	// Cool.Cat
	unsigned char *newKey = new unsigned char[25];
	memset(newKey,0,sizeof(newKey));
	this->Padding(pKey,kLen,newKey,24);

#ifdef DEBUG_KEY
	printf("InitKeyTriple.pKey[%s].newKey[%s]\n",pKey,newKey);
#endif

	unsigned long long pFake[32] = {0};
	memset(pFake,0,sizeof(pFake));

	// ---------------------------------------------------
	// MODE_EDE3 => enKnL/deKnR/enKn3 => deKn3/enKnR/deKnL
	// ---------------------------------------------------
	// enKnL		deKnR		enKn3
	// newKey		newKey[8]	newKey[16]
	// ---------------------------------------------------
	// deKnL		enKnR		deKn3
	// newKey		newKey[8]	newKey[16]
	// ---------------------------------------------------
	// deKnR->de
	deskey(&newKey[8], false,TYPE_TRIPLE);
	cpkey(deKnR[TYPE_TRIPLE],false,TYPE_TRIPLE);
	// enKn3->en
	deskey(&newKey[16], true,TYPE_TRIPLE);
	cpkey(enKn3[TYPE_TRIPLE],true,TYPE_TRIPLE);
	// enKnL->en
	deskey(newKey, true,TYPE_TRIPLE);
	// save fake
	for (int i=0;i<32;i++)
		pFake[i] = enKnL[TYPE_TRIPLE][i];
	// ----------------------
	// enKnR->en
	deskey(&newKey[8], true,TYPE_TRIPLE);
	cpkey(enKnR[TYPE_TRIPLE],true,TYPE_TRIPLE);
	// deKn3->de
	deskey(&newKey[16], false,TYPE_TRIPLE);
	cpkey(deKn3[TYPE_TRIPLE],false,TYPE_TRIPLE);
	// deKnL->de
	deskey(newKey, false,TYPE_TRIPLE);
	// save origin
	for (int i=0;i<32;i++)
		enKnL[TYPE_TRIPLE][i] = pFake[i];

	delete [] newKey;
	newKey = 0;
}

// 1重DES
void TDEA::DES_Single(unsigned char *pSrc,unsigned char *pDst,unsigned int dLen,bool bEncode)
{
	// 传入的加解密后的长度必须为8的倍数
	if (dLen%8)
	{
		assert(0);
		return;
	}

	unsigned long long work[2] = {0};

	// block ciphertext
	if (bEncode)
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,enKnL[TYPE_SINGLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
	else
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,deKnL[TYPE_SINGLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
}

// 2重DES（由初始化密钥时指定加解密模式为MODE_ED2）
// 3种加密方式(E=加密，D=解密)：
// 1. EE2：使用两个不同密钥（k1,k2）
// 2. ED2：使用两个不同密钥（k1,k2）
void TDEA::DES_Double(unsigned char *pSrc,unsigned char *pDst,unsigned int dLen,bool bEncode)
{
	// 传入的加解密后的长度必须为8的倍数
	if (dLen%8)
	{
		assert(0);
		return;
	}

	unsigned long long work[2] = {0};

	// block ciphertext
	if (bEncode)
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,enKnR[TYPE_DOUBLE]);
			desfunc(work,deKn3[TYPE_DOUBLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
	else
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,enKn3[TYPE_DOUBLE]);
			desfunc(work,deKnR[TYPE_DOUBLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
}

// 3重DES（由初始化密钥时指定加解密模式为MODE_EDE3）
// 3种加密方式(E=加密，D=解密)：
// 1. EEE3：使用三个不同密钥（k1,k2,k3）
// 2. EDE3：使用三个不同密钥（k1,k2,k3）
// 3. EEE2：使用两个不同密钥（k1=k3,k2）
// 4. EDE2：使用两个不同密钥（k1=k3,k2）
void TDEA::DES_Triple(unsigned char *pSrc,unsigned char *pDst,unsigned int dLen,bool bEncode)
{
	// 传入的加解密后的长度必须为8的倍数
	if (dLen%8)
	{
		assert(0);
		return;
	}

	unsigned long long work[2] = {0};

	// block ciphertext
	// ---------------------------------------------------
	// MODE_EDE3 => enKnL/deKnR/enKn3 => deKn3/enKnR/deKnL
	// ---------------------------------------------------
	// enKnL		deKnR		enKn3
	// newKey		newKey[8]	newKey[16]
	// ---------------------------------------------------
	// deKnL		enKnR		deKn3
	// newKey		newKey[8]	newKey[16]
	// ---------------------------------------------------
	if (bEncode)
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,enKnL[TYPE_TRIPLE]);
			desfunc(work,deKnR[TYPE_TRIPLE]);
			desfunc(work,enKn3[TYPE_TRIPLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
	else
	{
		for(unsigned int i=0;i<(dLen/8);i++)
		{
			scrunch((unsigned char *)(pSrc+i*8),work);
			desfunc(work,deKn3[TYPE_TRIPLE]);
			desfunc(work,enKnR[TYPE_TRIPLE]);
			desfunc(work,deKnL[TYPE_TRIPLE]);
			unscrun(work,(unsigned char *)(pDst+i*8));
		}
	}
}