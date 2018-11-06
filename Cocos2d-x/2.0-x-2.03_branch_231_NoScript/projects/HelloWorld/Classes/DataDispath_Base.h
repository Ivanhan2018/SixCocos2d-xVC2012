//
//  DataDispath_Base.h
//  XXDDZ
//
//  Created by XXY on 13-9-18.
//
//

#ifndef XXDDZ_DataDispath_Base_h
#define XXDDZ_DataDispath_Base_h

#include "Packet.h"
#include "cocos2d.h"

using namespace cocos2d;

/************************************************************************/
/* 数据处理的基类,该类继承了CCObject                                        */
/************************************************************************/
class DataDispath_Base:public CCObject
{
    
public:
	// 无参构造函数
	DataDispath_Base(void)
	{
        memset(m_pdata,0,sizeof(_BYTE_)*SOCKET_TCP_BUFFER);
	};
    
	// 析构函数
	virtual ~DataDispath_Base(void)
	{
		
	};
	// 初始化函数
	virtual bool init(void)
	{
		return true;
	};
	/**
     *设置操作对象类
     */
	bool setGameEngine(void *gameEngine)
	{
		this->m_GameEngine = gameEngine;
		return true;
	};
	/*
     *运行函数,该函数会被线程调用
     */
	virtual void run(void)
	{
		// 释放自己
		if(this!=0)
		{
			delete this;
		}
	};
    
protected:
	//主命令码
	_D_WORD_ mainCmd;
    
	//子命令码
	_D_WORD_ subCmd;
    
    //发送的数据
    _BYTE_ m_pdata[SOCKET_TCP_BUFFER];
    
	//数据长度
	_D_WORD_ m_sizeData;
    
	//游戏引擎的对象指针
	void *m_GameEngine;
};


#endif //XXDDZ_DataDispath_Base_h
