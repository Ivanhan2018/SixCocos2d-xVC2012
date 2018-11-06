#include "SIX_SceneMgr.h"

// ���Դ�Сд
extern int compareIgnoreCase(CCString str,const char * pStr);

void SIX_SceneMgr::ParseNode(SIX_XmlDataSet *pDataSet,const char *nodeName)
{
	if (compareIgnoreCase(pDataSet->getValue(),nodeName))
		return;

	// ���û���ӽڵ�
	if (!pDataSet->pNode || !pDataSet->pNode->GetChildrenCount())
		return;

	// �����ӽڵ�
	SIX_XmlDataSet *pChild = 0;
	CCARRAY_FOREACH_T(pDataSet->pNode->GetChildren(),pChild,SIX_XmlDataSet*)
	{
		if (compareIgnoreCase(pChild->getKey(),"Element") && compareIgnoreCase(pChild->getValue(),"Music"))
		{
			SIXLog("key=%s,value=%s",pChild->getKey().getCString(),pChild->getValue().getCString());
			continue;
		}

		// ��������
		SIX_SceneData *pScene = new SIX_SceneData();

		int col_count = 0;
		SIX_KV *pKV = 0;

		CCARRAY_FOREACH_T(pChild->pDataElement->GetChildren(),pKV,SIX_KV*)
		{
			if (!compareIgnoreCase(pKV->getKey(),"id"))
			{
				col_count++;
				pScene->setId(pKV->getValue().intValue());
			}
			else if (!compareIgnoreCase(pKV->getKey(),"path"))
			{
				col_count++;
				pScene->setPath(pKV->getValue().getCString());
			}
		}

		// ����ֶ�����һ��
		if (col_count!=2)
		{
			CC_SAFE_DELETE(pScene);
		}
		else
		{
			AddObjToDict(pScene,pScene->getId());

			SIXLog("Ԥ����[%d][%s][0x%08X][0x%08X]...OK",
				pScene->getId(),
				pScene->getPath().getCString(),
				pScene,
				pScene->GetScenePtr());
		}
	}
}

int SIX_SceneMgr::ParseXML(SIX_DSTPL<SIX_XmlDataSet> *pXmlDataSet)
{
	SIX_XmlDataSet *pDataSet = 0;
#ifdef DEBUG_PRINT
	unsigned int i=0;
#endif
	SIXLog("SIX_SceneMgr.Parse=%d",pXmlDataSet->GetChildrenCount());
	CCARRAY_FOREACH_T(pXmlDataSet->GetChildren(),pDataSet,SIX_XmlDataSet*)
	{
		// ����Root��Comment
		if (compareIgnoreCase(pDataSet->getKey(),"Element"))
			continue;

		// ��������
		ParseNode(pDataSet,"SceneList");
	}

	return 0;
}

int SIX_SceneMgr::Run()
{
	return 0;
}

int SIX_SceneMgr::Release()
{
	return 0;
}

// Ԥ���س���
int SIX_SceneMgr::preloadScene(SIX_SceneData *pScene)
{
	if (!pScene)
		return 3;
	if (!pScene->getPath().getCString())
		return 2;

	int retv = pScene->LoadScene();
	if (retv!=0)
		return retv;

	pScene->setIsPreload(true);

	return 0;
}

// �л�����
SIX_UIScene *SIX_SceneMgr::changeScene(int sceneIdx)
{
	SIXLog("�л�����[%d]==>����[%d]...",m_CurrentSceneIdx,sceneIdx);
	SIX_SceneData *pScene = dynamic_cast<SIX_SceneData*>(GetObjFromDict(sceneIdx));
	if (!pScene)
	{
		SIXLog("�л�����[%d]==>����[%d]...������!",m_CurrentSceneIdx,sceneIdx);
		return 0;
	}

	// ���������ûԤ����
	if (!pScene->getIsPreload())
	{
		int retv = preloadScene(pScene);
		if (retv!=0)
		{
			SIXLog("�л�����[%d]==>����[%d]...Ԥ����ʧ��!Errcode[%d]",m_CurrentSceneIdx,sceneIdx,retv);
			return 0;
		}
	}

	m_CurrentSceneIdx = sceneIdx;

	// �ͷŵ�ǰ����
	SIXLog("�л�����[%d]==>����[%d][0x%08X]...OK!",m_CurrentSceneIdx,sceneIdx,pScene);
	
	return pScene->GetScenePtr();
}

// ж�س�����ֻ�ͷ�CCScene�����ͷŸ���SIX_SceneData�������������л�
void SIX_SceneMgr::unloadScene(int sceneIdx)
{
	SIX_SceneData *pScene = (SIX_SceneData*)GetObjFromDict(sceneIdx);
	if (!pScene)
	{
		SIXLog("�ͷų���[%d]...������!",sceneIdx);
		return;
	}

	pScene->setIsPreload(false);
	SIXLog("�ͷų���[%d]...OK!",sceneIdx);
}

SIX_SceneData *SIX_SceneMgr::GetScenePointer(int sceneIdx)
{
	return dynamic_cast<SIX_SceneData*>(GetObjFromDict(sceneIdx));
}