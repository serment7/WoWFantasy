#include "stdafx.h"
#include "cStunState.h"
#include "cGameObject.h"

cStunState::cStunState()
{
	ZeroMemory(&m_packet,sizeof(m_packet));
	m_packet.msg_type = Msg_Idle;
}


cStunState::~cStunState()
{
}

void cStunState::EnterState(cGameObject * _entity)
{
}

void cStunState::ExitState(cGameObject * _entity)
{
}

void cStunState::Execute(cGameObject * _entity)
{
}

bool cStunState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_StunEnd:
		MessageCatch(_entity, m_packet);
		return true;
	}
	return false;
}