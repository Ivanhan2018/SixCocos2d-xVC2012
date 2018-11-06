/***********************************************
Name：场景管理器
Desc：场景加载、切换、释放
Auth：Cool.Cat@2013-03-18
***********************************************/
#pragma once
#include <SIX_EntityMgr.h>
#include <SIX_UIMgr.h>
#include <SIX_UIScene.h>
#include <CCLuaEngine.h>

USING_NS_CC;

//INTERFACE_BEGIN_BASED(SIX_SceneData,SIX_Interface)
//	CONSTRUCTOR(
//		SIX_SceneData,
//		m_Id = 0;
//		m_IsPreload = false;
//	)
//	// 唯一索引
//	CC_SYNTHESIZE(unsigned int,m_Id,Id);
//	// 相对路径
//	CC_SYNTHESIZE(CCString,m_Path,Path);
//	// 是否已预加载
//	CC_SYNTHESIZE(bool,m_IsPreload,IsPreload);
//INTERFACE_END()

class SIX_SceneData:public SIX_Interface{
public:
	SIX_SceneData()
	{
		m_Id = 0;
		m_IsPreload = false;
		m_Scene = 0;
	}
	~SIX_SceneData()
	{
		//CC_SAFE_DELETE(m_Scene);
		CC_SAFE_RELEASE(m_Scene);
	}
public:
	// 唯一索引
	virtual unsigned int getId()		{return m_Id;}
	virtual void setId(unsigned int Id)	{m_Id=Id;}

	// 相对路径
	virtual CCString getPath()			{return m_Path;}
	virtual void setPath(CCString Path)	{m_Path=Path;}

	// 是否已预加载
	virtual bool getIsPreload()					{return m_IsPreload;}
	virtual void setIsPreload(bool IsPreload)	{m_IsPreload=IsPreload;}

	SIX_UIScene *GetScenePtr()					{return m_Scene;}

	int LoadScene()
	{
		CCLuaEngine* pEngine = CCLuaEngine::defaultEngine();

		//std::string dirPath = SCRIPT_PATH;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//CCString* pstrFileContent = CCString::createWithContentsOfFile((m_Path.getCString()).c_str());
		CCString* pstrFileContent = CCString::createWithContentsOfFile(m_Path.getCString());
		if (pstrFileContent)
		{
			pEngine->executeString(pstrFileContent->getCString());
		}
#else
		//std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath((dirPath + m_Path.getCString()).c_str());
		std::string path = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(m_Path.getCString());
		//pEngine->addSearchPath(path.substr(0, path.find_last_of("/") - dirPath.length()).c_str());

		// 加载场景脚本，同时回传场景指针
		int retv = pEngine->executeScriptFile(path.c_str());
		if (retv!=0)
		{
			SIXLog("加载场景脚本[%s]...失败！",m_Path.getCString());
			return 1;
		}
#endif

		// 栈顶置零
		lua_settop(pEngine->getLuaState(),0);
		lua_getglobal(pEngine->getLuaState(),"pScene");
		
		void *pLuaAddr = ::lua_touserdata(pEngine->getLuaState(),1);
		if (!pLuaAddr)
			return 3;

		// lua传回来的类指针地址要处理下
		// Cool.Cat
		SIXLog("场景对象指针A = 0x%08X/0x%08X/0",this,pLuaAddr);
		m_Scene = REV_ADDR(SIX_UIScene,pLuaAddr);
		SIXLog("场景对象指针B = 0x%08X/0x%08X/0x%08X",this,m_Scene,m_Scene->GetScene());

		//// executeGlobalFunction调用lua函数，只有当函数返回值为整形时
		//// 才能传出并接受到。。。
		//// Cool.Cat@2013-03-29
		//retv = pEngine->executeGlobalFunction("LoadXML");
		//if (retv!=1)
		//	return ERROR_INFO::ERROR_OBJECT_NIL;
		return 0;
	}
public:
	unsigned int m_Id;
	CCString m_Path;
	bool m_IsPreload;
	SIX_UIScene *m_Scene;
};

class SIX_SceneMgr:public SIX_EntityMgr,public TSingleton<SIX_SceneMgr> {
	//CONSTRUCTOR(
	//	SIX_SceneMgr,
	//	m_SceneList = new SIX_DSTPL<SIX_XmlDataSet>;
	//);
	//DESTRUCTOR(
	//	SIX_SceneMgr,
	//	Release();
	//	CC_SAFE_DELETE(m_SceneList);
	//);
public:
	SIX_SceneMgr()
	{
		//m_SceneList = new SIX_DSTPL<SIX_XmlDataSet>;
		m_PreloadCount = 0;
		m_CurrentSceneIdx = 0;
	}
	~SIX_SceneMgr()
	{
		Release();
		//CC_SAFE_DELETE(m_SceneList);
	}
public:
	void ParseNode(SIX_XmlDataSet *pDataSet,const char *nodeName);
	virtual int ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet);
	virtual int Run();
	virtual int Release();
public:
	void SetSceneResourceFolder(const char *folder)		{m_SceneBasePath = CCString::create(folder);}
	unsigned int GetTotalSceneCount()					{return this->GetObjCount();}
	unsigned int GetPreloadSceneCount()					{return m_PreloadCount;}
	int GetCurrentSceneIdx()							{return m_CurrentSceneIdx;}
	void unloadScene(int sceneIdx);
	int preloadScene(SIX_SceneData *pScene);
	SIX_UIScene *changeScene(int sceneIdx);
	SIX_SceneData *GetScenePointer(int sceneIdx);
public:
	//SIX_DSTPL<SIX_XmlDataSet> *m_SceneList;
	CCString *m_SceneBasePath;
	unsigned int m_PreloadCount;
	int m_CurrentSceneIdx;
};