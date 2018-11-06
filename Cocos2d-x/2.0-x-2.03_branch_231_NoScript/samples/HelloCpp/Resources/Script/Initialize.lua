--[[
----------------------------------
Lua部分入口
------------------------------------
Cool.Cat@2013/3/27 15:42:49
------------------------------------
]]

-- avoid memory leak
collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

-- 依赖项
require	"Script/Enum/ControlEvent"
require "Script/Common/Utility"
require	"Script/Common/Global"
require "Script/Common/Variable"
require "Script/TestFunc"
require "Script/TestHttp"
require "Script/MusicMgr"
require "Script/SceneMgr"

require "Script/Common/extern"
require	"Script/ExControl/VisibleRect"
require	"Script/ExControl/Console"
require "Script/ExControl/DragBox"
require "Script/ExControl/PopWnd"
require "Script/ExControl/MsgBox"

require "Script/Enum/NetEvent"
require "Script/NetWork/NetWork"
require "Script/NetWork/Game"

CCLuaLog("Initialized...")

local platform = CCApplication:sharedApplication():getTargetPlatform()
if (platform==kTargetWindows) then
	local title = APPNAME.." ver:"..VersionStr()
	CCEGLView:sharedOpenGLView():setWindowTitle(SIX_Utility:GetInstance():U2G(title))
	CCEGLView:sharedOpenGLView():setWindowIcon("./iphonehd/icon.ico")
	CCEGLView:sharedOpenGLView():setFrameSize(1024,650)
end

-- 测试C++<=>Lua交互接口
TestFunc()

-- 测试Http交互接口
--TestHttp()

-- Socket
--InitNetWork()

-- 客户端通讯逻辑
InitGameLogic("127.0.0.1",5150,"杨二","123")

-- 加载音乐
LoadMusic("Music","SoundList.xml")

-- 加载场景
if (LoadScene("iphonehd","SceneList.xml")==0) then
	CCLuaLog("Initialized...Failed!")
	return
end
CCLuaLog("Initialized...OK!")