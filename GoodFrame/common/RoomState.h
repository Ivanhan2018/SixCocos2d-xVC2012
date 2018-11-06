
#ifndef ROOM_STATE_H
#define ROOM_STATE_H

#include "./RoomInfo.h"

// ����״̬
class __declspec(dllexport) CRoomState
{
public:
	CRoomState(void);
	~CRoomState(void);

public:
	/* --------------------------------------------------------------------------
	����˵�������÷���״̬
	���������
		bAdd		TRUE  ��ʾ����һ�� roomSate ֵ��״̬ ��
		            FALSE ��ʾ�Ƴ�һ�� roomSate ֵ��״̬
		roomSate	��״ֵ̬
	--------------------------------------------------------------------------*/
	void room_state(BOOL bAdd, LONGLONG roomSate);

	// ��÷���״̬������ֵ�ο� ROOM_STATE
	LONGLONG room_state();

	// ���õ�¼���䣬�β� TRUE ��ʾ����FALSE ��ʾ��ֹ��
	void set_login(BOOL	bAllow);

	// �ܷ��¼���䣬����ֵ TRUE ��ʾ����FALSE ��ʾ��ֹ��
	BOOL can_login();

	// �������£��β� TRUE ��ʾ����FALSE ��ʾ��ֹ��
	void set_sit_down(BOOL	bAllow);

	// �ܷ����£�����ֵ TRUE ��ʾ����FALSE ��ʾ��ֹ��
	BOOL can_sit_down();

private:
	LONGLONG m_lRoomState;	// ����״̬���ο� ROOM_STATE
};

#endif