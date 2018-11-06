#ifndef GLOBAL_FIELD_HEAD_FILE
#define GLOBAL_FIELD_HEAD_FILE
#pragma once
#include "GlobalDef.h"
//////////////////////////////////////////////////////////////////////////

//????��????��
/*struct tagDataDescribe
{
	WORD							wDataSize;						//????��?�C��
	WORD							wDataDescribe;					//????��???
    tagDataDescribe()
    {
        wDataSize = 0;
        wDataDescribe = 0;
    }
};*/

//////////////////////////////////////////////////////////////////////////

//?��??�C��?��
#define DTP_NULL					0								//??�C?????

//a?����C��?��
//a?����C��?��
#define DTP_USER_ID					1								//����a? I D
#define DTP_GAME_ID					2								//����a? I D
#define	DTP_USER_ACCOUNTS			3								//����a?�����ҡ�
#define	DTP_USER_PASS				4								//����a?��???
#define DTP_USER_GENDER				5								//����a?�C����?
#define DTP_USER_FACE				6								//����a??��?��
#define DTP_USER_RIGHT				7								//����a?????
#define DTP_MASTER_RIGHT			8								//��??��????
#define	DTP_UNDER_WRITE				9								//��?�C��??��?
#define	DTP_LOVE_LINESS				10								//����a?????
#define	DTP_NICK_NAME				11								//����a?��?��?
#define	DTP_USER_SORT				12								//�֡֡�?
//?��?���C��?��
#define DTP_USER_STATUS				100								//����a??��?��
#define DTP_USER_TABLE				101								//��??��??�ҡ�
#define DTP_USER_CHAIR				102								//��??���ҡ�??
#define DTP_USER_PING				103								//?��?������?��
#define DTP_USER_INDEX				104								//����a?��?��?
#define DTP_USER_ROUND				105								//����a��o???
#define DTP_LOOK_ON_USER			106								//�֡��Ѐ?��o��

//a?�ơ¨C��?��
#define DTP_USER_WIN				200								//?��?�¡�???
#define DTP_USER_LOST				201								//?��?�¡�???
#define DTP_USER_DRAW				202								//��??�¡�???
#define DTP_USER_FLEE				203								//?��?�¡�???
#define DTP_WIN_RATE				204								//����a??��??
#define DTP_LOST_RATE				205								//����a??��??
#define DTP_DRAW_RATE				206								//����a?��???
#define DTP_FLEE_RATE				207								//����a??��??
#define DTP_USER_TAX				208								//����a?����?��
#define DTP_INSURE_SCORE			209								//�������馸?����
#define DTP_GAME_GOLD				210								//��??�Ʀ�?����
#define DTP_USER_SCORE				211								//����a?�ơ�??
#define DTP_USER_PLAY_COUNT			212								//???�¡�???
#define DTP_USER_EXPERIENCE			213								//����a??�١���
#define DTP_GAME_LEVEL				214								//��??�Ʀ�?o?
#define DTP_COMMUNITY_LEVEL			215								//����?����?o?

//??���ШC��?��
#define DTP_USER_GROUP_ID			300								//����?�� I D
#define DTP_USER_GROUP_NAME			301								//����?�֡�??��
#define DTP_USER_NOTE				302								//����a?����?��
#define DTP_USER_DESCRIBE			303								//����a?��???
#define DTP_USER_COMPANION			304								//����a?��??��
#define DTP_USER_ZIP_CODE			305								//����a?��?��? by 20100925 ����a?
#define DTP_USER_CITY				306								//��??�C�C��?�� by 20100925 ����a?
#define DTP_USER_VISITOR			307								//�Ƿ��ο�
#define DTP_USER_Keepdays			308								// �������� by 20120401 ljl
#define DTP_USER_PlayCount			309								// ������ľ���
#define DTP_USER_GetPoint			310								// �����õ���
#define DTP_USER_PrizeInfo			311								// �����콱���
#define DTP_USER_TotalCount			312								// �ܾ���
#define DTP_USER_RelieveCount		313								// �ȼ�

//?��?�ݨC��?��
#define DTP_COMPUTER_ID				1000							//a�B??�C��?�C
#define DTP_STATION_PAGE			1001							//��?��?���ݡ̨�
#define DTP_OPTION_BUFFER			1002							//�֡�¡̨C��?��
#define DTP_GAME_KIND				1003							// ��Ϸ����

//?��?��???��
#define DTP_MESSAGE_ID				2000							//???��id
#define DTP_ADDRESSER				2001							//�ơ�o??��
#define DTP_TITLE					2002							//����??
#define DTP_CONTENT					2003							//????
#define DTP_MESSAGE_TIME			2004							//?��o��
//////////////////////////////////////////////////////////////////////////


union UKeepLogonDays
{
	DWORD dwVaule[3];
	struct
	{
		DWORD	dwTodayScore;
		DWORD	dwTomorrowScore;
		DWORD	canGet:1;
		DWORD	days:31;
	};

	UKeepLogonDays()
	{
		memset(this, 0, sizeof(*this));
	}
};

//????��?��?�¨B??
class CSendPacketHelper
{
	//����????��?
protected:
	WORD								m_wDataSize;					//????��?�C��
	WORD								m_wBufferSize;					//a�ҡ�?��?�C��
	BYTE								* m_pcbBuffer;					//a�ҡ�?�¡ǡ�?

	//��?????��?
public:
	//�ЦС�?��???
	CSendPacketHelper(void * pcbBuffer, WORD wBufferSize)
	{
		m_wDataSize=0;
		m_wBufferSize=wBufferSize;
		m_pcbBuffer=(BYTE *)pcbBuffer;
	}
	//??�ЦС�???
	virtual ~CSendPacketHelper() {}

	//��???��???
public:
	//???��????
	void CleanData() { m_wDataSize=0; }
	//a��?�㣤?�C��
	WORD GetDataSize() { return m_wDataSize; }
	//a��?��a�ҡ�?
	void * GetDataBuffer() { return m_pcbBuffer; }
	//��???????
	bool AddPacket(void * pData, WORD wDataSize, WORD wDataType)
	{
		//�C?������?�C��
		//ASSERT((wDataSize+sizeof(tagDataDescribe)+m_wDataSize)<=m_wBufferSize);
		if ((wDataSize+sizeof(tagDataDescribe)+m_wDataSize)>m_wBufferSize) return false;

		//��???????
		//ASSERT(m_pcbBuffer!=NULL);
		tagDataDescribe * pDataDescribe=(tagDataDescribe *)(m_pcbBuffer+m_wDataSize);
		pDataDescribe->wDataSize=wDataSize;
		//pDataDescribe->wDataDescribe=wDataType;

		//��???????
		if (wDataSize>0)
		{
			//ASSERT(pData!=NULL);
			memcpy(pDataDescribe+1,pData,wDataSize);
		}

		//��?�¡�????
		m_wDataSize+=sizeof(tagDataDescribe)+wDataSize;
	
		return true;
	}
};

/////////////////////////////////////////////////////////////////////////////////////////

class CRecvPacketHelper
{

protected:
	WORD								m_wDataPos;						
	WORD								m_wDataSize;					
	BYTE								* m_pcbBuffer;				

public:
	CRecvPacketHelper(void* pcbBuffer, WORD wDataSize)
	{
		m_wDataPos=0;
		m_wDataSize=wDataSize;
		m_pcbBuffer=(BYTE *)pcbBuffer;
	}
	
	virtual ~CRecvPacketHelper() {}

	
public:
	void * GetData(tagDataDescribe & DataDescribe)
	{
		if (m_wDataPos>=m_wDataSize) 
		{
			assert(m_wDataPos==m_wDataSize);
			DataDescribe.wDataSize=0;
			//DataDescribe.wDataDescribe=DTP_NULL;
			return NULL;
		}

		assert((m_wDataPos+sizeof(tagDataDescribe))<=m_wDataSize);
		memcpy(&DataDescribe,m_pcbBuffer+m_wDataPos,sizeof(tagDataDescribe));
        
        //����������
        //int a = m_wDataPos+sizeof(tagDataDescribe)+DataDescribe.wDataSize;
		//assert((m_wDataPos+sizeof(tagDataDescribe)+DataDescribe.wDataSize)<=m_wDataSize);

        if ((m_wDataPos+sizeof(tagDataDescribe)+DataDescribe.wDataSize) > m_wDataSize)
        {
           // CCLOG("�������������������������������������ݽ���쳣������������������������");
        }
        
        

		if ((m_wDataPos+sizeof(tagDataDescribe)+DataDescribe.wDataSize)>m_wDataSize)
		{
			DataDescribe.wDataSize=0;
			//DataDescribe.wDataDescribe=DTP_NULL;
			return NULL;
		}

		void * pData=NULL;
		if (DataDescribe.wDataSize>0) pData=m_pcbBuffer+m_wDataPos+sizeof(tagDataDescribe);
		m_wDataPos+=sizeof(tagDataDescribe)+DataDescribe.wDataSize;
		return pData;
	};
};

//////////////////////////////////////////////////////////////////////////

#endif