#ifndef __ROTA__TE_MENU_H__
#define __ROTA__TE_MENU_H__
#include "cocos2d.h"
#include <vector>

USING_NS_CC;

class GameItemLayer :public cocos2d::CCLayer
{
public:
    //���췽��
    CREATE_FUNC(GameItemLayer);
    //��Ӳ˵���
    void addMenuItem(cocos2d::CCMenuItem *item);
    //����λ��
    void updatePosition();
    //����λ�ã��ж���
    void updatePositionWithAnimation();
    //λ�ý���  �޸ĽǶ� forwardΪ�ƶ�����  ������1/3����1
    //true Ϊ����  false ��
    void rectify(bool forward);
    //��ʼ��
    virtual bool init();
    //����  ��������ת�Ƕ���Ϊ0
    void reset();
	void setEnabled(bool flag);
private:
    //���ýǶ� ����
    void setAngle(float angle);
    float getAngle();
    //���õ�λ�Ƕ� ����
    void setUnitAngle(float angle);
    float getUnitAngle();
    //��������ת���Ƕ�,ת������Ϊ  �ƶ����Menu.width����_unitAngle
    float disToAngle(float dis);
    //���ر�ѡ�е�item
    cocos2d::CCMenuItem * getCurrentItem();
private:
    //�˵��Ѿ���ת�Ƕ� ����
    float _angle;
    //�˵����,_children˳���仯���½����鱣��˳��
    std::vector<cocos2d::CCMenuItem *> _items;
    //��λ�Ƕ� ����
    float _unitAngle;
    //��������
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);   
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
   
	virtual void registerWithTouchDispatcher();
	//���������ú���
    void actionEndCallBack(float dx);
    //��ǰ��ѡ���item
    cocos2d::CCMenuItem *_selectedItem;
    //��������ʱ��
     float animationDuration;
	 bool inFlag;
};
#endif
 
