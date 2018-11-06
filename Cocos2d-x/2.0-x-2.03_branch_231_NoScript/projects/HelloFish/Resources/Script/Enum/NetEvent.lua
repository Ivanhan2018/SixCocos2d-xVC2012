--[[
----------------------------------
网络事件
------------------------------------
Cool.Cat@2013/4/19 15:48:19
------------------------------------
]]

NetEvent = {
	MainCode = {
		-- 断开
		ErrorCode			=	0x00,
		
		-- 单向包(本房间内消化)
		ONEWAY 				= 0x01,
		
		-- 广播包(跨房间聊天等)
		BORADCAST			=	0x02,
	},
	SubCode = {
		-- 断开
		ErrorCode			=	0x00,
		
		-- 心跳
		HEARTBEAT			=	0x01,
		
		-- SQL
		TSQL					=	0x02,	
		
		-- 登录
		LOGIN					=	0x03,
		-- 退出
		LOGOUT				=	0x04,
		
		-- 获取当前房间桌子信息
		DESK_LIST			=	0x05,
		-- 坐下
		DESK_SITDOWN	=	0x06,
		-- 起立
		DESK_STANDUP	=	0x07,
		
		-- 进入场景
		SCENE_ENTER		=	0x08,
		-- 退出场景
		SCENE_EXIT		=	0x09,
		
		-- 船体变动
		SHIP_MOVE			=	0x0A,
		
		-- 子弹发射
		BULLET_FIRE		=	0x0B,
		-- 子弹命中
		BULLET_HIT		=	0x0C,
		
		-- 金币变动
		GOLD_CHANGE		=	0x0D,
		
		-- 结算
		SETTLEMENT		=	0x0E,
		
		-- 聊天
		CHAT					=	0x0F,
		-- 表情
		EMOTE					=	0x10,
		
		-- balabala
	}
}