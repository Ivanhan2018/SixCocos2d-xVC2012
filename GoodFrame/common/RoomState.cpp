
#include "./PublicHead.h"
#include "./RoomState.h"

CRoomState::CRoomState(void)
{
	m_lRoomState = 0;	// 参考 ROOM_STATE

	set_login(TRUE);
	set_sit_down(TRUE);
}

CRoomState::~CRoomState(void)
{
}

// 设置房间状态
void CRoomState::room_state(BOOL bAdd, LONGLONG roomSate)
{
	if(bAdd) // 增加状态
	{
		m_lRoomState |= (LONGLONG)roomSate;
	}
	else	// 减掉状态
	{
		LONGLONG lTmp01 = (LONGLONG)roomSate;
		LONGLONG lTmp02 = ~lTmp01;	// 取反

		m_lRoomState &= lTmp02;
	}
}

// 获得房间状态，反回值参考 ROOM_STATE
LONGLONG CRoomState::room_state()
{
	return m_lRoomState;
}

// 设置登录房间，形参 TRUE 表示允许，FALSE 表示禁止，
void CRoomState::set_login(BOOL	bAllow)
{
	room_state(bAllow, (LONGLONG)RS_CAN_LOGIN);
}

// 能否登录房间，返回值 TRUE 表示允许，FALSE 表示禁止，
BOOL CRoomState::can_login()
{
	LONGLONG lTmp = m_lRoomState & RS_CAN_LOGIN;
	return (0 != lTmp);
}

// 设置坐下，形参 TRUE 表示允许，FALSE 表示禁止，
void CRoomState::set_sit_down(BOOL	bAllow)
{
	room_state(bAllow, (LONGLONG)RS_CAN_SIT);
}

// 能否坐下，返回值 TRUE 表示允许，FALSE 表示禁止，
BOOL CRoomState::can_sit_down()
{
	LONGLONG lTmp = m_lRoomState & RS_CAN_SIT;
	return (0 != lTmp);
}