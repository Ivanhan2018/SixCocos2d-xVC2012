/*
** desc: 游戏实体类
** code: zhouwei
** date: 2013.06.9
*/

#ifndef	__ENTITYMGR_H__
#define __ENTITYMGR_H__

#include "ans/AnsSingleton.h"
//#include "ans/BaseObject.h"
#include "msgDispatch/MsgDispatch.h"
#include "Login.h"
#include "RoomFrame.h"

class EntityMgr : public ans::Singleton<EntityMgr, CCObject>
{
private:
	SINGLETON_FRIEND_SUB(EntityMgr, CCObject);
	EntityMgr();
	~EntityMgr();
public: 
    MsgDispatch* getDispatch() { return m_pDispatch; }

	Login* login() { return m_pLogin; }
	RoomFrame* roomFrame(){ return m_pRoomFrame; }

	std::string& getMacAddress() {return macAddress;}
    void setMacAddress(const char* mac);
	void setDownLoadPesent(int pesent,int gameID);
	int getPesent(int gameID);
	int m_nDownLoadPe;
	bool m_bIsShowRuker;

private:
	Login* m_pLogin;
	RoomFrame* m_pRoomFrame;
    MsgDispatch* m_pDispatch;
    bool m_bLogin;             //登陆状态（登陆服务器或者游戏服务器）
	std::string macAddress;
	int m_nDownLoadPesent[4];
};


#endif //__ENTITYMGR_H__