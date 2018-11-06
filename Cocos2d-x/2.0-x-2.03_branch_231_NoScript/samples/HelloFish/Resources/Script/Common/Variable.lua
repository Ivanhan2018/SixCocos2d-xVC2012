--[[
------------------------------------
全局变量
------------------------------------
Cool.Cat@2013-4-16 0:41:00
------------------------------------
]]

-- 名称
APPNAME	=	"欢乐捕鱼"

-- 版本
VERSION = {
	MAIN	=	1,
	CHILD	=	1,
	STAGE = 0,
	BUILD = 0405,
	DESC	=	"Beta",
	DATE	=	"2013/4/25 13:46:02"
}

CCS2DX = "Cocos2d-2.0-x-2.0.3"

-- 开发者模式
DEVELOPER_MODE = false
DEVELOPER_LASTTIME = 0

-- 连接状态
CONNECTED = false

-- 是否退出
NEEDEXIT = false

-- CCLog限制=8K
MAX_LEN = 8*1024

-- app尺寸
gWinSize = CCDirector:sharedDirector():getWinSize()

-- TCP/IP协议枚举
Enum_PROTOCOL = {
	"TCP",
	"UDP",
	"RAW",
	"DAM",
	"SEQ",
};

PROTOCOL = ENUM(Enum_PROTOCOL)

-- 键盘消息
Enum_KeyBord = {WM_KEYDOWN = 0x0100,WM_KEYUP = 0x0101,WM_CHAR = 0x0102}

KEY_WPARAM = {
	VK_ESCAPE		=	0x1B,
	-- ~
	--VK_OEM_3		= 0xC0,
	VK_NUMPAD0	= 0x60,
	VK_RETURN 	= 0x0D,
	VK_SHIFT		= 0x10,
	VK_CONTROL	= 0x11,
	VK_NUMPAD1	= 0x61,
	VK_NUMPAD6	= 0x66,
	VK_NUMPAD9	= 0x69,
}

-- 按下的键（WM_KEYDOWN 时为真，WM_KEYUP时 或没有按的情况下 为假）
-- 用来处理 Ctrl,Shift,Alt 键是否按下
PRESS_KEY = { [KEY_WPARAM.VK_SHIFT] = nil }

-- 上一个场景索引
LAST_SCENE_IDX	=	-1