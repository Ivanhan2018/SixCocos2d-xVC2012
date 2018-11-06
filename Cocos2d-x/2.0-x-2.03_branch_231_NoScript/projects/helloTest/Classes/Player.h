#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Player : public CCObject
{
public:
	Player();
	~Player();
	void updatePkWeiZhi();//�����Ƶ�λ��
	
private:
	CC_SYNTHESIZE(bool,m_isDiZhu,IsDiZhu);//�Ƿ�Ϊ����
	CC_SYNTHESIZE(bool,m_isCall,Call);//�Ƿ��ѽе���
	CC_SYNTHESIZE(int,m_iCallNum,CallNum);//�е����ķ���
	CC_SYNTHESIZE(CCArray*,m_arrPk,ArrPk);//����ӵ�е��˿���
	CC_SYNTHESIZE(CCPoint,m_point,Point);//��������ĳ�ʼλ��
	CC_SYNTHESIZE(int,m_iPlayerClass,PlayerClass);//�������:0Ϊ��ң�1Ϊ���ԣ�2Ϊ��ʾ��������,3Ϊ���Ҫ�����ƣ�4Ϊ����1Ҫ�����ƣ�5Ϊ����2Ҫ������
	std::vector<PaiXing> m_vecPX;//��������
	CC_SYNTHESIZE(bool,m_isOutPk,IsOutPk);//����Ƿ����true:�� false:����
};

