#pragma once
#include "PublicComponents/TableComponents/FrameOneRoom.h"
//#include "PlazaComponents/FramePlaza.h"

CFrameOneRoom *CFrameOneRoom::frameOneRoomWithGameServer(void *server, int index)
{
	CFrameOneRoom *cFrameOneRoom = new CFrameOneRoom();
	cFrameOneRoom->InitFrameOneRoomWithGameServer(server, index);
	return cFrameOneRoom;
}

void CFrameOneRoom::InitFrameOneRoomWithGameServer(void *server, int index)
{
	CCLayer::init();
	memset(&m_GameServer, 0, sizeof(tagGameServer));
	memcpy(&m_GameServer, server, sizeof(tagGameServer));

	m_nTableCount	= 6;
	m_nRoomIndex	= index;
	m_nPageIndex	= 0;
	m_RuleScore     = 20;
	this->m_pRoomName = "";
}


//���뷿���¼�
void CFrameOneRoom::quickEnterGame(CCObject *pSender)
{
	
	// ���ٽ��뷿��
	      // important
    //if ([CFramePlaza shareFramePlaza].m_cbType == SCROLLTYPE_ROOM)
	{
		// ��ʾ
		//CFramePlaza::shareFramePlaza()->showFrameSpinnerView("���ڲ���λ��..."/*@"���ڲ���λ��..."*/, true);
		
		// ���ӵ�ַ
		/*string
		NSString* address = [NSString CreateStringWithTHCAR:self.m_GameServer.szServerAddr size:sizeof(self.m_GameServer.szServerAddr)];
		if ([address compare:@"127.0.0.1"] == NSOrderedSame)
			address = [CFrameDate shareFrameDate].m_pAddress;
		[[CFrameDate shareFrameDate] DoConnect:address port:self.m_GameServer.wServerPort];
		
		// ���õ�¼��ʶ
		[CFrameDate shareFrameDate].m_wBehaviorFlags = (BEHAVIOR_LOGON_IMMEDIATELY|VIEW_MODE_PART);
		
		// ���뷿��
		[[CFrameDate shareFrameDate] SendPacketWithEnterRoomPageCount:m_nTableCount];
		
		// ��¼��ʶ
		[CFrameDate shareFrameDate].m_wBehaviorFlags = BEHAVIOR_LOGON_NORMAL;
		[CFrameDate shareFrameDate].m_bStartType = true;
        
        // ���÷�������
        NSString* roomName=[NSString CreateStringWithTHCAR:self.m_GameServer.szServerName size:sizeof(self.m_GameServer.szServerName)];
        [[CFramePlaza shareFramePlaza] setObject:roomName key:@"roomName"];*/
        
	}
}

void CFrameOneRoom::ButtonEventWithEnterRoom(CCObject *pSender)
{
    //NSLog(@"ButtonEventWithEnterRoom enter");
    
	// ��õȴ��ؼ�
	/*[[CFramePlaza shareFramePlaza] showFrameSpinnerView:@"���ڽ��뷿��..." close:YES];
	
	// ���ñ�ʶ
	[CFrameDate shareFrameDate].m_wBehaviorFlags = (BEHAVIOR_LOGON_NORMAL|VIEW_MODE_PART);
	
	// ���ӷ���
	NSString* address=[NSString CreateStringWithTHCAR:m_GameServer.szServerAddr size:sizeof(m_GameServer.szServerAddr)];
	if ([address compare:@"127.0.0.1"] == NSOrderedSame)
		address=[CFrameDate shareFrameDate].m_pAddress;
	[[CFrameDate shareFrameDate] DoConnect:address port:m_GameServer.wServerPort];
	
	// ���ͽ�����Ϣ
	[[CFrameDate shareFrameDate] SendPacketWithEnterRoomPageCount:m_nTableCount];
	
	// ������ʶ
	[CFrameDate shareFrameDate].m_bStartType = false;
    
    // ���÷�������
    [[CFramePlaza shareFramePlaza] setObject:m_pRoomName key:@"roomName"];*/
}

void CFrameOneRoom::ccTouchesEnded (CCSet *pTouches, CCEvent *pEvent)
{
	CCTouch *touch = (CCTouch *)pTouches->anyObject();
	CCPoint location = touch->getLocationInView();
	CCRect rect = this->boundingBox();
	if (rect.containsPoint(location))
    {
        this->quickEnterGame(NULL);
    }
}