#include "SHA.h"

void SHA::Hash160(Big *hash,const char *src,int slen)
{
	char s[20]={0};
    sha sh;
    shs_init(&sh);
    for (int i=0;i<slen;i++)
    {
        shs_process(&sh,src[i]);
    }
    shs_hash(&sh,s);
    *hash=from_binary(20,s);
}

void SHA::Hash256(Big *hash,const char *src,int slen)
{
	char s[32]={0};
    sha256 sh;
    shs256_init(&sh);
    for (int i=0;i<slen;i++)
    {
        shs256_process(&sh,src[i]);
    }
    shs256_hash(&sh,s);
    *hash=from_binary(32,s);
}

void SHA::Hash384(Big *hash,const char *src,int slen)
{
	char s[48]={0};
    sha384 sh;
    shs384_init(&sh);
    for (int i=0;i<slen;i++)
    {
        shs384_process(&sh,src[i]);
    }
    shs384_hash(&sh,s);
    *hash=from_binary(48,s);
}

void SHA::Hash512(Big *hash,const char *src,int slen)
{
	char s[64]={0};
    sha512 sh;
    shs512_init(&sh);
    for (int i=0;i<slen;i++)
    {
        shs512_process(&sh,src[i]);
    }
    shs512_hash(&sh,s);
    *hash=from_binary(64,s);
}