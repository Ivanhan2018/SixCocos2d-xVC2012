//
//  UserItem.h
//  Game
//
//  Created by zhouwei on 13-6-21.
//
//

#ifndef __Game__UserItem__
#define __Game__UserItem__

#include <iostream>
#include "IUserItem.h"

//�û���Ϣ��
class CUserItem : public IUserItem
{
	//��������
public:
	//���캯��
	CUserItem();
    
    CUserItem(tagUserData* tag);
	//��������
	virtual ~CUserItem();
    
	//�����ӿ�
public:
    
	//����ӿ�
public:
	//�����ж�
	virtual bool  IsActive() { return m_bActive; }
    
	//���Խӿ�
public:
	//��Ϸ����
	virtual unsigned int getUserPlayCount();
	//�û� I D
	virtual DWORD getUserID() { return m_UserData.dwUserID; }
    //�û�id
    virtual unsigned int getFaceID() { return m_UserData.wFaceID; }
	//�û�����
	virtual  char* getUserName() { return m_UserData.szName; }
	//��ȡ�û�
	virtual tagUserData * getUserData() { return &m_UserData; }
    //��ȡ�û����Ӻ�
    virtual unsigned int getChairID() { return m_UserData.wChairID; }
    //�����û����Ӻ�
    virtual void setChairID(unsigned int nChairID) { m_UserData.wChairID =  nChairID; }
    //��ȡ�û����Ӻ�
    virtual unsigned int getTableID() { return m_UserData.wTableID; }
    //�����û����Ӻ�
    //virtual void setTableID(unsigned int nTableID){ m_UserData.wTableID = nTableID; }
	//���ýӿ�
public:
	//���û���
	virtual void setUserScore(const tagUserScore * pUserScore);
	virtual void setUserScore(const tagMobileUserScore * pUserScore);
	//���ý��
	virtual void setUserGold(const tagUserGold * pUserGold);
	//����״̬
	virtual void setUserStatus(const tagUserStatus * pUserStatus);
	//��������
	virtual void setUserSort(const unsigned int nSortID, const EN_MatchStatus enMatchStatus);
	//���ñ�������
	virtual void setUserMatchScore(const unsigned int nMatchScore);
    
	//���ܺ���
public:
    //�����û�����
    void setUserDate(tagUserData* tag);
    
	//��������
	void cleanData();
    
    //��������
public:
	tagUserData						m_UserData;						//�û���Ϣ
    
	//�ڲ�����
private:
	bool							m_bActive;						//������Ч
};


#endif /* defined(__Game__UserItem__) */
