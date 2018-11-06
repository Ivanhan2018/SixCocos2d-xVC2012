//  [4/1/2014 wucan]

#ifndef		__VIEW_TASK__
#define		__VIEW_TASK__
#include "DDZLogic.h"
#include "DDZRes.h"
#include "cocos2d.h"
USING_NS_CC;

class ViewTask:public CCNode
{
public:
	CREATE_FUNC(ViewTask);
	virtual bool init();
	void setBackTaskView(BYTE* _data,WORD _num);									//--���Ʊ�������
	void setLastTaskView(WORD _key);														//--����������
	CCNode * m_dpNode;		//���Ƽӱ�
	CCNode * m_jsNode;		//�����Ƽӱ�
private:
	CCLabelTTF * addTaskString(char * key,CCPoint point,_ccColor3B color,int fontSize);
};
#endif