#ifndef ENCRYPT_HEAD_FILE
#define ENCRYPT_HEAD_FILE

//数组维数
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

//////////////////////////////////////////////////////////////////////////
//网狐32位MD5加密和20位异或加密解密
//MD5 加密类
class CMD5Encrypt
{
	//函数定义
private:
	//构造函数
	CMD5Encrypt() {}

	//功能函数
public:
	//生成密文
	static void EncryptData(const char* pszSrcData, char szMD5Result[33]);
};


//异或加密类
class CXOR6601Encrypt
{
	//函数定义
private:
	//构造函数
	CXOR6601Encrypt() {}

	//功能函数
public:
	//生成密文
	static unsigned short EncryptData(const char* pszSrcData, char* pszEncrypData, unsigned short wSize,int encrypt_key_len=5);
	//解开密文
	static unsigned short CrevasseData(const char* pszEncrypData, char* pszSrcData, unsigned short wSize,int encrypt_key_len=5);
};


//MD5 加密类
class CMD5
{
	//变量定义
private:
	unsigned long int				state[4];
	unsigned long int				count[2];
	unsigned char					buffer[64];
	unsigned char					PADDING[64];

	//函数定义
public:
	//构造函数
	CMD5() { MD5Init(); }

	//功能函数
public:
	//最终结果
	void MD5Final(unsigned char digest[16]);
	//设置数值
	void MD5Update(unsigned char * input, unsigned int inputLen);

	//内部函数
private:
	//初始化
	void MD5Init();
	//置位函数
	void MD5_memset(unsigned char * output, int value, unsigned int len);
	//拷贝函数
	void MD5_memcpy(unsigned char * output, unsigned char * input, unsigned int len);
	//转换函数
	void MD5Transform(unsigned long int state[4], unsigned char block[64]);
	//编码函数
	void Encode(unsigned char * output, unsigned long int * input, unsigned int len);
	//解码函数
	void Decode(unsigned long int *output, unsigned char * input, unsigned int len);
};


#endif