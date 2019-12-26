#pragma once
#ifndef _CHECK_ID_CARD_H_
#define _CHECK_ID_CARD_H_

#ifdef WIN32
#include <time.h>
#else
#include <sys/time.h>
typedef struct {
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#endif

////////////////////////////////////////////////////////////////////////////
// 功能描述:  获取当前年、月、日、时、分、秒
static bool GetCurCalendar(int& year, int& month, int& day, int& hour, int& minute, int& second);

class cCheckIdCard
{
public:
    cCheckIdCard(void);
    //身份证验证
    bool CheckIDCard(const std::string& Id);
    
    //18位身份证验证
    bool CheckIDCard18(const std::string& Id);

    //15位身份证验证
    bool CheckIDCard15(const std::string& Id);

   //生日验证
    bool CheckDate(const std::string& Year,   const std::string& Month,   const std::string&   Day);

	// 是否超过N岁
	bool GetAge(const std::string& Id,int iAge);
   
    //最后一位校验
    bool VarifyCode(const std::string& Id);
   
    //实现身份证的15位转18位 
    std::string per15To18(const std::string& Id);

    //获得生日
    std::string getBirthday(const std::string& Id);

    virtual ~cCheckIdCard(void);
};

#endif


