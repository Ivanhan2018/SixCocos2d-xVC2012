2.0.3和2.2.x例程说明：
1、SimpleGame、HelloUI、CCControl的PC和Android版(i809)均可跑
2、SIX_MusicMgr测试，PC可跑
3、PC版弹出一个CCLayerColor
4、ClickAndMoveTest、LabelTest、UserDefaultTest、MenuTest，PC可跑
5、仅仅改了库名CocosDenshionEx，PC版调用C++ DLL，CHSInt128类有问题
6、ADT+Builder/VC2012+Cocos2d-x 2.0.3可以正常编译捕鱼原型CCControl的Android版和PC版
7、
2015年7月4日
SimpleGame的PC和Android版均可跑
2016年6月15日
HelloWorld_2.0.3_20140906、HelloWorld20140906、ApplicationDemo更名为SimpleGame1，HelloWorld更名为SimpleGame
python create_project.py -project SimpleGame1 -package org.cocos2dx.application1 -language cpp
Builders
New_Builder_20150704
F:\android-ndk-r9\ndk-build.cmd
F:\hxhwin7\Cocos2d-xVC2010\cocos2d-2.0-x-2.0.3\samples\SimpleGame1
NDK_PROJECT_PATH=F:\hxhwin7\Cocos2d-xVC2010\cocos2d-2.0-x-2.0.3\samples\SimpleGame1\proj.android
8、
2015年5月31日
链接失败
2016年6月15日
PC和Android可跑
HelloWorld_2.0.3_20140906Fish、HelloWorld、ApplicationDemo更名为BJL
python create_project.py -project BJL -package org.cocos2dx.bjl -language cpp
9、
setDesignResolutionSize设置设计分辨率和适配方式
kResolutionNoBorder适配方式,虽然没有黑边,但背景和UI都有可能显示在屏幕之外;
10、
SIX_PopWndSetting::onEnterTransitionDidFinish()|SIX_ScrollBar::create|SIX_ScrollBar::initWithSprites|CCNode::addChild(CCNode *child)|CCNode::addChild(CCNode *child, int zOrder, int tag)断言失败

11、捕鱼原型2.2.5版本ApplicationDemo2.2.5
文件名大小写敏感
鱼和子弹、船、金币、游戏场景
加载XML
texture查找filename
老H捕鱼

12、MyFish
ApplicationDemo425
HelloFish124@20150525
2.0.3+VC2010的HelloFish代码移到2.2.6+VC2012下，暂时不能编译通过
MyFishV1R0@20180329
[SIX_UIScene::InitUIMgr](16) ==> 场景初始化...
[SIX_UIScene::InitUIMgr](22) ==> 场景初始化...OK!
[SIX_XMLParser::LoadXMLFromFile](23) ==> LoadXMLFromFile.Parse[Game.xml].Error[2]=Failed to open file
[SIX_SceneGame::init](52) ==> SIX_SceneGame.init.retv[2]
[SIX_SceneGame::~SIX_SceneGame](30) ==> ~SIX_SceneGame
崩溃堆栈：
 	libcocos2d.dll!cocos2d::CCObject::retainCount() 行 110	C++
 	SimpleGame2.x.exe!SIX_UIScene::~SIX_UIScene() 行 10	C++
 	SimpleGame2.x.exe!SIX_SceneGame::~SIX_SceneGame() 行 31	C++
 	SimpleGame2.x.exe!SIX_SceneGame::`scalar deleting destructor'(unsigned int)	C++
>	SimpleGame2.x.exe!SIX_SceneGame::scene() 行 35	C++
 	SimpleGame2.x.exe!AppDelegate::applicationDidFinishLaunching() 行 48	C++
 	libcocos2d.dll!cocos2d::CCApplication::run() 行 47	C++

SixFish背景图尺寸：1280*733
Fish背景图尺寸：1204*650
HelloHttp合入
i809 2.2可跑@20150613
protobuf-2.4.1合入@20150529
萝莉快跑合入@20150530