#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

unsigned int getUint(unsigned char H,unsigned char A,unsigned char B,unsigned char L)
{
	unsigned int ret=0;
	ret+=L;
	ret+=B*256;
	ret+=A*65536;
	ret+=H*16777216;
	return ret;
}

unsigned int getUintWH(unsigned char H,unsigned char A,unsigned char B,unsigned char L)
{
	return getUint(L,B,A,H);
}

/*
32字节的联合体
第一种用四个字节来表示；
第二种用两个双字节来表示；
第三种用一个长整型来表示。
*/
typedef struct
{
	union
	{
		struct { unsigned char s_b1,s_b2,s_b3,s_b4; } S_un_b;
		struct { unsigned short s_w1,s_w2; } S_un_w;
		unsigned int S_addr;
		struct { signed char s_c1,s_c2,s_c3,s_c4; } S_s_c;
		int S_addr_s;
	};
	void print()
	{
	  cout<<S_addr<<"(WHSIX反值)="<<(int)S_un_b.s_b1<<"."<<(int)S_un_b.s_b2<<"."<<(int)S_un_b.s_b3<<"."<<(int)S_un_b.s_b4<<endl;
	}
}S_un;

int main(int argc, char* argv[])
{
	if(argc>=3 && strcmp(argv[1],"-i")==0)
	{	
		char *str=argv[2];
                int a,b,c,d;
		sscanf(str,"%d.%d.%d.%d",&a,&b,&c,&d);
                cout<<getUintWH(a,b,c,d)<<endl;	
                return 0;		
	}
        if(argc>=3 && strcmp(argv[1],"-s")==0)
        {
                char *str=argv[2];
                S_un int32;
                int32.S_addr=atoi(str);
                int32.print();
                return 0;
        }

	cout<<getUint(192,168,1,108)<<endl;//3232235884
	cout<<getUintWH(192,168,1,108)<<endl;//1812048064

	//inet_addr
        cout<<getUintWH(192,168,1,112)<<endl;//1879156928

	S_un int32;
	int32.S_addr=1812048064;//1812048064=192.168.1.108
	S_un int32a;//实现inet_addr的功能
	int32a.S_un_b.s_b1=192;
	int32a.S_un_b.s_b2=168;
	int32a.S_un_b.s_b3=1;
	int32a.S_un_b.s_b4=108;
	int32.print();
	int32a.print();
	S_un dwServerAddr;
	dwServerAddr.S_addr=1879156928;//1879156928=192.168.1.112
	dwServerAddr.print();
	S_un dwCNCServerAddr;
	dwCNCServerAddr.S_addr=3232235884;//3232235884=108.1.168.192
	dwCNCServerAddr.print();

	return 0;
}
