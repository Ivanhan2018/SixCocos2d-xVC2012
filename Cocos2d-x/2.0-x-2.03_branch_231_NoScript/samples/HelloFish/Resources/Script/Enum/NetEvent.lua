--[[
----------------------------------
�����¼�
------------------------------------
Cool.Cat@2013/4/19 15:48:19
------------------------------------
]]

NetEvent = {
	MainCode = {
		-- �Ͽ�
		ErrorCode			=	0x00,
		
		-- �����(������������)
		ONEWAY 				= 0x01,
		
		-- �㲥��(�緿�������)
		BORADCAST			=	0x02,
	},
	SubCode = {
		-- �Ͽ�
		ErrorCode			=	0x00,
		
		-- ����
		HEARTBEAT			=	0x01,
		
		-- SQL
		TSQL					=	0x02,	
		
		-- ��¼
		LOGIN					=	0x03,
		-- �˳�
		LOGOUT				=	0x04,
		
		-- ��ȡ��ǰ����������Ϣ
		DESK_LIST			=	0x05,
		-- ����
		DESK_SITDOWN	=	0x06,
		-- ����
		DESK_STANDUP	=	0x07,
		
		-- ���볡��
		SCENE_ENTER		=	0x08,
		-- �˳�����
		SCENE_EXIT		=	0x09,
		
		-- ����䶯
		SHIP_MOVE			=	0x0A,
		
		-- �ӵ�����
		BULLET_FIRE		=	0x0B,
		-- �ӵ�����
		BULLET_HIT		=	0x0C,
		
		-- ��ұ䶯
		GOLD_CHANGE		=	0x0D,
		
		-- ����
		SETTLEMENT		=	0x0E,
		
		-- ����
		CHAT					=	0x0F,
		-- ����
		EMOTE					=	0x10,
		
		-- balabala
	}
}