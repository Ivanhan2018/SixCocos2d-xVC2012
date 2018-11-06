
#ifndef ROOM_STATE_H
#define ROOM_STATE_H

#include "./RoomInfo.h"

// 房间状态
class __declspec(dllexport) CRoomState
{
public:
	CRoomState(void);
	~CRoomState(void);

public:
	/* --------------------------------------------------------------------------
	函数说明：设置房间状态
	传入参数：
		bAdd		TRUE  表示增加一个 roomSate 值的状态 ，
		            FALSE 表示移除一个 roomSate 值的状态
		roomSate	新状态值
	--------------------------------------------------------------------------*/
	void room_state(BOOL bAdd, LONGLONG roomSate);

	// 获得房间状态，反回值参考 ROOM_STATE
	LONGLONG room_state();

	// 设置登录房间，形参 TRUE 表示允许，FALSE 表示禁止，
	void set_login(BOOL	bAllow);

	// 能否登录房间，返回值 TRUE 表示允许，FALSE 表示禁止，
	BOOL can_login();

	// 设置坐下，形参 TRUE 表示允许，FALSE 表示禁止，
	void set_sit_down(BOOL	bAllow);

	// 能否坐下，返回值 TRUE 表示允许，FALSE 表示禁止，
	BOOL can_sit_down();

private:
	LONGLONG m_lRoomState;	// 房间状态，参考 ROOM_STATE
};

#endif