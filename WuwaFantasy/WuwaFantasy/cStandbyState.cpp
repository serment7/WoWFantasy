#include "stdafx.h"
#include "cStandbyState.h"
#include "cGameObject.h"
#include "cAction.h"

cStandbyState::cStandbyState()
{
}

cStandbyState::~cStandbyState()
{
}

void cStandbyState::EnterState(cGameObject * _entity)
{
}

void cStandbyState::ExitState(cGameObject * _entity)
{
}

void cStandbyState::Execute(cGameObject * _entity)
{
}

bool cStandbyState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Standby:
		return true;
	default:
		return MessageCatch(_entity, _packet);
	}
	
}
