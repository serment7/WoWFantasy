#include "stdafx.h"
#include "cIdleState.h"
#include "cGameObject.h"
#include "cMoveState.h"

cIdleState::cIdleState()
{
}

cIdleState::~cIdleState()
{
}

void cIdleState::EnterState(cGameObject * _player)
{
}

void cIdleState::ChangeState(cGameObject * _player)
{
}

void cIdleState::ExitState(cGameObject * _player)
{
}

void cIdleState::Execute(cGameObject * _player)
{
}

bool cIdleState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	}

	return false;
}

void cIdleState::OnActionDelegate(cAction * _pSender)
{

}
