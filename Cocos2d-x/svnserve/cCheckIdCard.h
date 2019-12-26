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
// ��������:  ��ȡ��ǰ�ꡢ�¡��ա�ʱ���֡���
static bool GetCurCalendar(int& year, int& month, int& day, int& hour, int& minute, int& second);

class cCheckIdCard
{
public:
    cCheckIdCard(void);
    //���֤��֤
    bool CheckIDCard(const std::string& Id);
    
    //18λ���֤��֤
    bool CheckIDCard18(const std::string& Id);

    //15λ���֤��֤
    bool CheckIDCard15(const std::string& Id);

   //������֤
    bool CheckDate(const std::string& Year,   const std::string& Month,   const std::string&   Day);

	// �Ƿ񳬹�N��
	bool GetAge(const std::string& Id,int iAge);
   
    //���һλУ��
    bool VarifyCode(const std::string& Id);
   
    //ʵ�����֤��15λת18λ 
    std::string per15To18(const std::string& Id);

    //�������
    std::string getBirthday(const std::string& Id);

    virtual ~cCheckIdCard(void);
};

#endif


