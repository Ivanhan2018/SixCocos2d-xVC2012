#include "SIX_Console.h"

SIX_Console::~SIX_Console()
{
}

SIX_Console *SIX_Console::Create(float x,float y,const ccColor4B& color, float width, float height,bool bRedrawBorder,bool bCloseThenCleanup)
{
	// 如果都没运行场景，还弹什么窗口呢？。。。
	// Cool.Cat
	CCScene *pScene = CCDirector::sharedDirector()->getRunningScene();
	if (!pScene)
		return 0;

	SIX_Console *pConsole = new SIX_Console();
	if (pConsole && pConsole->init())
	{
		pConsole->initWithColor(color,width,height);
		pConsole->setPosition(x,y);
		pConsole->setRedrawBorder(bRedrawBorder);
		pConsole->setTouchEnabled(true);
		pConsole->m_ForbiddenTouch = true;
		pConsole->m_bCloseThenCleanup = bCloseThenCleanup;
		pConsole->setObjName("SIX_Console");
	}
	return pConsole;
}

bool SIX_Console::init()
{
	if (!SIX_PopWnd::init())
		return false;

	__EditBoxH = 30;
	__PaddingLR = 5;
	__PaddingT = 5;
	__HeaderH = 15;
	__SubmitW = 60;

	return true;
}

void SIX_Console::onEnterTransitionDidFinish()
{
	pListView = 0;
	pEditBox = 0;
	pTitleTTF = 0;
	pRuntimeTTF = 0;
	m_LastShowTime = 0.0;
	InitTitle("Console");
	InitRuntime("");
	InitEditBox();
	InitListView();
	DoEnter();
	schedule(schedule_selector(SIX_Console::update), 0.01f);
}

void SIX_Console::update(float t)
{
	setRuntime(GetFormatRuntime());
}

const char *SIX_Console::GetFormatRuntime()
{
	double sec = SIX_Utility::GetInstance()->GetGlobalSecond();

	int day = SIX_Utility::GetInstance()->getIntPart(sec / 86400);
	sec = sec - day * 86400;

	int hour = SIX_Utility::GetInstance()->getIntPart(sec / 3600);
	sec = sec - hour * 3600;

	int min = SIX_Utility::GetInstance()->getIntPart(sec / 60);
	sec = sec - min * 60;

	if (day==0)
		return CCString::stringWithFormat("已经运行：%02d:%02d:%05.2f",hour,min,sec)->getCString();
	return CCString::stringWithFormat("已经运行：%02d(D):%02d:%02d:%05.2f",day,hour,min,sec)->getCString();
}

void SIX_Console::setRuntime(const char *text)
{
	if (!pRuntimeTTF)
		return;
	pRuntimeTTF->setString(SIX_Utility::GetInstance()->G2U(text).c_str());
	SIX_Utility::GetInstance()->FixedTexParameters(pRuntimeTTF->getTexture());
}

void SIX_Console::setContent(const char *fmt,...)
{
	if (!pListView)
		return;

	char szBuf[1024] = {0};

    va_list ap;
    va_start(ap,fmt);
	vsnprintf(szBuf,1023,fmt,ap);
    va_end(ap);
	
	SIX_ListViewCell *pCell = new SIX_ListViewCell();
	pListView->AppendCell(pCell);
	
	CCLabelTTF *pContent = CCLabelTTF::create();
	
	pContent->setString(SIX_Utility::GetInstance()->G2U(szBuf).c_str());
	pContent->setColor(ccc3(255,255,255));
	pContent->setOpacity(255);
	pContent->setAnchorPoint(ccp(0,0));
	pContent->setPosition(ccp(0,0));
	pContent->setContentSize(CCSize(getContentSize().width-__PaddingLR*2,getContentSize().height-__HeaderH-__EditBoxH-__PaddingT*4));
	SIX_Utility::GetInstance()->FixedTexParameters(pContent->getTexture());
	pCell->addChild(pContent);
}

void SIX_Console::ShowConsole(CCLayer *pThis)
{
	pFather = pThis;
	double now = SIX_Utility::GetInstance()->GetGlobalSecond();
	if (now-m_LastShowTime<0.05)
		return;

	m_LastShowTime = now;
		
	Show(!m_IsShow);
}

void SIX_Console::InitTitle(const char *text)
{
	if (pTitleTTF || !text)
		return;
	pTitleTTF = CCLabelTTF::create();
	pTitleTTF->setString(strlen(text)?text:" ");
	pTitleTTF->setColor(ccc3(255,255,255));
	pTitleTTF->setOpacity(255);
	pTitleTTF->setAnchorPoint(ccp(0,0));
	pTitleTTF->setPosition(ccp(__PaddingLR,getContentSize().height-__HeaderH-__PaddingT));
	SIX_Utility::GetInstance()->FixedTexParameters(pTitleTTF->getTexture());
	addChild(pTitleTTF);
}

void SIX_Console::InitRuntime(const char *text)
{
	if (pRuntimeTTF || !text)
		return;
	pRuntimeTTF = CCLabelTTF::create();
	pRuntimeTTF->setString(strlen(text)?text:" ");
	pRuntimeTTF->setColor(ccc3(0,255,0));
	pRuntimeTTF->setOpacity(255);
	pRuntimeTTF->setAnchorPoint(ccp(0,0));
	pRuntimeTTF->setPosition(ccp(getContentSize().width-155,getContentSize().height-__HeaderH-__PaddingT));
	SIX_Utility::GetInstance()->FixedTexParameters(pRuntimeTTF->getTexture());
	pRuntimeTTF->setContentSize(CCSize(150,pRuntimeTTF->getContentSize().height));
	// -- 设置无效。。。
	//pRuntimeTTF->setHorizontalAlignment(kCCTextAlignmentRight);
	addChild(pRuntimeTTF);
}


void SIX_Console::InitEditBox()
{
	if (pEditBox)
		return;
	pEditBox = new SIX_EditBox();
	pEditBox->setPosition(ccp(__PaddingLR,__PaddingLR));
	pEditBox->setContentSize(CCSize(getContentSize().width-__PaddingLR*2-__SubmitW,__EditBoxH));
	// -- 文字输入上限
	pEditBox->setInputTextMaxCount(80);
	pEditBox->getTTF()->setPosition(ccp(5,5));
	pEditBox->getTTF()->setFontSize(14);
	// -- 默认提示文字
	pEditBox->getTTF()->setPlaceHolder("CMD>");
	SIX_Utility::GetInstance()->FixedTexParameters(pEditBox->getTTF()->getTexture());
	// -- 提示文字颜色
	pEditBox->getTTF()->setColorSpaceHolder(ccc3(0,255,255));
	// -- 输入文字颜色
	pEditBox->getTTF()->setColor(ccc3(0,255,255));
	addChild(pEditBox);
	
	// -- 输入光标
	pEditBox->InitCursor(0xFFFFFFFF,2,16);
}

void SIX_Console::InitListView()
{
	if (pListView)
		return;

	SIX_UILayer *pContainer = SIX_UILayer::create(ccc4(0,0,0,0));
	pContainer->setContentSize(CCSize(getContentSize().width-__PaddingLR*2,getContentSize().height-__HeaderH-__EditBoxH-__PaddingT*4));
	pContainer->setPosition(ccp(__PaddingLR,__EditBoxH+__PaddingT*2));

	//SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
	//			"scrollbar.png",CCRect(0,51,17,17),CCRect(17,0,getContentSize().height-__HeaderH-__EditBoxH-__PaddingT*4-17*2,17),
	//			"scrollbar.png",CCRect(0,0,17,17),
	//			"scrollbar.png",CCRect(0,17,17,17),
	//			"scrollbar.png",CCRect(0,34,17,17),
	//			false
	//		);

	SIX_ScrollBar *pScrollBar = SIX_ScrollBar::create(
		"scrollbar.png",CCRect(0,51,17,17),CCSize(getContentSize().height-__HeaderH-__EditBoxH-__PaddingT*4-17*2,17),
		"scrollbar.png",CCRect(0,51,17,17),
		"scrollbar.png",CCRect(0,34,17,17),
		"scrollbar.png",CCRect(0,34,17,17),
		"scrollbar.png",CCRect(0,0,17,17),
		"scrollbar.png",CCRect(0,17,17,17),
		CCSize(17,17),
		false
		);
	pScrollBar->setAnchorPoint(ccp(0,0));
	pScrollBar->setMinimumValue(0);
	pScrollBar->setMaximumValue(100);
	pScrollBar->setValue(0);
	pScrollBar->setDefaultTouchPriority(m_nPriority-1);

	pListView = SIX_ListView::create(ccc4(0,0,0,0),
				ccp(__PaddingLR,__EditBoxH+__PaddingT*2),
				CCSize(getContentSize().width-__PaddingLR*2,getContentSize().height-__HeaderH-__EditBoxH-__PaddingT*4),
				CCSize(getContentSize().width-__PaddingLR*2,18),
				kCCScrollViewDirectionVertical,
				pContainer,
				pScrollBar
			);

	pListView->setObjName("ConsoleList");
	
	// -- 设置响应touch事件(create的时候已经设置好了，这里只是演示而已)
	pListView->setTouchEnabled(true);
	
	// -- 设置裁剪超出区域(create的时候默认设置为true，这里只是演示而已~)
	pListView->getTableView()->setClippingToBounds(true);
	// -- 设置横竖方向(create的时候已经设置好了，这里只是演示而已~)
	pListView->getTableView()->setDirection(kCCScrollViewDirectionVertical);
	// -- 设置自上而下滚动(create的时候已经设置好了，这里只是演示而已~)
	pListView->getTableView()->setVerticalFillOrder(kCCTableViewFillTopDown);
	// -- 设置滑动效果
	pListView->getTableView()->setBounceable(false);
	addChild(pListView);
}

void SIX_Console::DoEnter()
{
	if (isVisible()==false)
		return;
	if (pEditBox)
		pEditBox->attachWithIME();
}

// -- 响应回车
void SIX_Console::OnInputDone(CCLayer *pLayer,const char *text)
{
#ifdef WIN32
	SIX_EditBox *pThis = (SIX_EditBox*)pLayer;
	if (!pThis || !pThis->getParent())
		return;
	if (!pFather)
		return;
	pThis->getTTF()->detachWithIME();
	pFather->OnProcessCommand(text);
	pThis->getTTF()->setString("");
	SIX_Utility::GetInstance()->FixedTexParameters(pThis->getTTF()->getTexture());
#endif
}