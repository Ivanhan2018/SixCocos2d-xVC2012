//
//  RoomFrame.h
//  ������
//
//  Created by zhouwei on 13-6-21.
//
//

#ifndef __Game__RoomFrame__
#define __Game__RoomFrame__

#include <iostream>
#include "event/GBEvent.h"
#include "event/GBEventIDs.h"
#include "ans/BaseObject.h"
#include "common/Define.h"
#include "common/GlobalDef.h"
#include "globalUnits/GlobalUnits.h"
#include "UserItem.h"
#include "cocos2d.h"
#include <map>

typedef std::vector<DWORD> UsrIdList;
typedef std::vector<tagUserData*> UsrDateList;

#define ERROR_CODE_LOGIN        (101)
#define	US_NULL				0x00					// û��״̬
#define US_FREE				0x01					// վ��״̬
#define US_SIT				0x02					// ����״̬
#define US_READY			0x03					// ͬ��״̬
#define US_LOOKON			0x04					// �Թ�״̬
#define US_PLAYING			0x05					// ��Ϸ״̬
#define US_OFFLINE			0x06					// ����״̬

class RoomFrame : public BaseObject,cocos2d::CCObject
{
public:
	RoomFrame();
	~RoomFrame();
	void reset();
public:
	//��ԭ������Ϸ��Ϣ�ֳɷ����½��Ϣ����Ϸ��Ϣ			add by wangjun   2014-12-15
	bool  OnEventTcpRoomRead(CMD_Command* pCommand,void* pData,WORD wDataSize);
	bool  OnEventTcpGameRead(CMD_Command* pCommand,void* pData,WORD wDataSize);
public:
	void onRoomMsg(GBEventConstArg& arg);
	void onGameMsg(GBEventConstArg& arg);		//��Ϸ��Ϣ���� add by wangjun 2014-12-15

public:
	//������Ϸ��������½��
	void sendLoginPacket();

	//�����Ŷ�����
	void sendQueuePacket(int cbQueueCell = 0);
public:
	/******************************��Ϸ��������Ϣ*******************************************/
	//��¼��Ϣ
	bool			OnSocketGameLogin(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û���Ϣ
	bool			OnSocketGameUser(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool			OnSocketGameInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//״̬��Ϣ
	bool			OnSocketGameStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//ϵͳ��Ϣ
	bool            OnSocketGameSystem(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//������Ϣ
	bool            OnSocketGameServerInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);


	/******************************��Ϸ�������û���Ϣ*******************************************/
	//�û�����
	bool OnSocketSubUserCome(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�����û�����
	bool OnSocketSubMatchUserCome(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�״̬
	bool OnSocketSubStatus(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubScore(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubSort(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�Ȩ��
	bool OnSocketSubRight(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//��Ա�ȼ�
	bool OnSocketSubMemberOrder(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//����ʧ��
	bool OnSocketSubSitFailed(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�����
	bool OnSocketSubChat(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û�˽��
	bool OnSocketSubWisper(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�������
	bool OnSocketSubUserInvite(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�μӱ���
	bool OnSocketJoinMatch(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�޸��û����
	bool OnSocketSubGold(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�޸��ǳ�
	bool OnSocketSubModifyNickName(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//��Ϸ������Ϣ
	bool OnSocketGameMatchInfo(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//vip����������Ϣ
	bool OnSocketVIPRoomPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//vip�����������
	bool OnSocketVIPErrorPassWord(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	//�û������ɼ�
	bool OnSocketSubMatchScore(CMD_Command* pCommand, void * pBuffer, WORD wDataSize);
	/****************************************************************************************/

	//��������ֵ��������
	bool			OnSocketGameOrder(void * pBuffer, WORD wDataSize);

	bool OnFrameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);
	bool OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize);

	//�ͻ��˿�ʼ��Ϸ
	void OnClientStartGame();

	//��ʼ�ͻ�����Ϸ
	void startClientGame();
public:
	//��ȡ�û��Լ���Ϣ
	CUserItem* getMeUserItem(){ return  m_pMeUserItem;}
	tagUserData* getMeUserDate() { &(m_pMeUserItem->m_UserData); }
public:
	IUserItem* insertItem(tagUserData* tag);
	IUserItem* insertItem(IUserItem* item);

	void removeItem(DWORD dwUserID);
	IUserItem* getUserItem(DWORD dwUserID);

	//�������Ƴ�
	void removeItemByTable(unsigned int nTableID,unsigned int nChairID);

	//���·����б�״̬
	void updateUserStatus(DWORD dwUserID, const tagUserStatus* pUserStatus);

	//�����û�����״̬
	void updateTableUserStatus(unsigned int nTableID,unsigned int nChairID,IUserItem* pUserItem);

	//�����Լ�����
	void updateMeTable(DWORD nUserID);
	UsrIdList searchUser(WORD wTableID);
	UsrDateList searchUserDate(WORD wTableID);

	// �����¼�������봦��       add by wangjun
	//��¼�ɹ�
	bool OnSocketSubGRLogonSuccess(void *buffer, WORD size);			
	//��¼ʧ��
	bool OnSocketSubGRLogonFailure(void *buffer, WORD size);		
	//��¼���
	bool OnSocketSubGRLogonFinish(void *buffer, WORD size);	
	//��ʾ����
	bool OnSocketSubGRUpdateNotify(void *buffer, WORD size);	
	//������½�ɹ���ʾ
	bool OnSocketSubGRLogonNotify(void *buffer, WORD size);

	// ������Ϣ�������봦��       add by wangjun
	//�б�����
	bool OnSocketSubGRConfigColumn(void *buffer, WORD size);			
	//��������
	bool OnSocketSubGRConfigServer(void *buffer, WORD size);		
	//��������
	bool OnSocketSubGRConfigPropepty(void *buffer, WORD size);		
	//�������
	bool OnSocketSubGRConfigFinish(void *buffer, WORD size);
	
	void setGameIsStart(bool flag){gameIsStart = flag;};
private:

	typedef std::map<DWORD, IUserItem*> UsrDateMap;
	//UsrDateMap m_UserDateMap;                     //�����û��б�

	CUserItem* m_pMeUserItem;

	unsigned int m_nChair;
	unsigned int m_nTable;

	UsrDateMap m_UserDateList;

	//add by wangjun 2014-12-19
	BYTE m_cbGameStatus;							//��Ϸ״̬
	BYTE m_cbAllowLookon;							//�����Թ�

	BYTE m_cbStatus;								//��Ϸ״̬��Ϣ
	bool gameIsStart;								//��Ϸ�Ƿ�ʼ��ʶ
};

#endif /* defined(__Game__RoomFrame__) */
