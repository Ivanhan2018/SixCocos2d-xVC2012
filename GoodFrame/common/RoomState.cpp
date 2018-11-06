
#include "./PublicHead.h"
#include "./RoomState.h"

CRoomState::CRoomState(void)
{
	m_lRoomState = 0;	// �ο� ROOM_STATE

	set_login(TRUE);
	set_sit_down(TRUE);
}

CRoomState::~CRoomState(void)
{
}

// ���÷���״̬
void CRoomState::room_state(BOOL bAdd, LONGLONG roomSate)
{
	if(bAdd) // ����״̬
	{
		m_lRoomState |= (LONGLONG)roomSate;
	}
	else	// ����״̬
	{
		LONGLONG lTmp01 = (LONGLONG)roomSate;
		LONGLONG lTmp02 = ~lTmp01;	// ȡ��

		m_lRoomState &= lTmp02;
	}
}

// ��÷���״̬������ֵ�ο� ROOM_STATE
LONGLONG CRoomState::room_state()
{
	return m_lRoomState;
}

// ���õ�¼���䣬�β� TRUE ��ʾ����FALSE ��ʾ��ֹ��
void CRoomState::set_login(BOOL	bAllow)
{
	room_state(bAllow, (LONGLONG)RS_CAN_LOGIN);
}

// �ܷ��¼���䣬����ֵ TRUE ��ʾ����FALSE ��ʾ��ֹ��
BOOL CRoomState::can_login()
{
	LONGLONG lTmp = m_lRoomState & RS_CAN_LOGIN;
	return (0 != lTmp);
}

// �������£��β� TRUE ��ʾ����FALSE ��ʾ��ֹ��
void CRoomState::set_sit_down(BOOL	bAllow)
{
	room_state(bAllow, (LONGLONG)RS_CAN_SIT);
}

// �ܷ����£�����ֵ TRUE ��ʾ����FALSE ��ʾ��ֹ��
BOOL CRoomState::can_sit_down()
{
	LONGLONG lTmp = m_lRoomState & RS_CAN_SIT;
	return (0 != lTmp);
}