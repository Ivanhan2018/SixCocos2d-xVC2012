#ifndef __FrameOneRoom__
#define __FrameOneRoom__

#include "common/Define.h"
#include "common/struct.h"

class CFrameOneRoom: public CCLayer
{
	//��
private:
	int										m_nRoomIndex;			// ������		0
	int										m_nPageIndex;			// ��ǰ����ҳ		0
	int										m_nTableCount;			// ������     Ĭ�ϣ�6

	long long                               m_RuleScore;            // ������� �����ʲô�á�

	tagGameServer							m_GameServer;			// ������Ϣ

	string									m_pRoomName;            // ��������
public :
	int getRoomIndex(){return m_nRoomIndex;};
	void setRoomIndex(int flag){m_nRoomIndex = flag;};
	int getPageIndex(){return m_nPageIndex;};
	void setPageIndex(int index){m_nPageIndex = index;};
	tagGameServer getTagGameServer(){return m_GameServer;};
	void setTagGameServer(tagGameServer server){m_GameServer = server;};
	string getRoomName(){return m_pRoomName;};
	void setRoomName(string name){m_pRoomName = name;};
	//��������
	void InitFrameOneRoomWithGameServer(void *server, int index);
	static CFrameOneRoom *frameOneRoomWithGameServer(void *server, int index);
	//��������¼�
	void quickEnterGame(CCObject *pSender);
	void ButtonEventWithEnterRoom(CCObject *pSender);
	virtual void  ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent);
};


#endif