#include <stdio.h>
#include <string>
using namespace std;

#include "cCheckIdCard.h"
#define PLAY_YEAR	(6)		//防沉迷验证 定义6岁以上才可以玩

class CFunction 
{ 
public: 
	CFunction() 
	{ 
		data = new char[64]; 
	}; 
	~CFunction() 
	{ 
		delete [] data; 
	}; 
	char *data; 
}; 

class CFunctionEx : public CFunction 
{ 
public: 
	CFunctionEx() 
	{ 
		m_data = new char[64]; 
	}; 
	~CFunctionEx() 
	{ 
		delete [] m_data; 
	}; 
private: 
	char *m_data; 
}; 

int main(int argc, char* argv[]) 
{ 
	//CFunction *pCFun = new CFunctionEx; 
	//delete pCFun;
	string	strIdCard;// 实名认证身份证号
    if(argc>1)
	{
		strIdCard=argv[1];
	}
    else
	{
		printf("usage: ./cCheckIdCard0 arg1\n例如:\n./cCheckIdCard0 420984198605231625\n");
		return 0;
	}	

	cCheckIdCard m_check_Id_Card;	// 验证身份证号	
	if (!m_check_Id_Card.CheckIDCard(strIdCard))
	{
		printf("身份证号码格式错误，请重新输入15或18位身份证号码。\n");
	}
	else if (!m_check_Id_Card.GetAge(strIdCard, PLAY_YEAR))
	{
		printf("您未满%d周岁哦，请在家长监护下完成认证！\n", PLAY_YEAR);
	}	
	else
	{
		printf("您的身份证号码格式验证通过，且已满6周岁。\n");
	}	
	return 0;
} 