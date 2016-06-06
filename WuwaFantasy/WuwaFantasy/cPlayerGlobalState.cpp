#include "stdafx.h"
#include "cPlayerGlobalState.h"
#include"cGameObject.h"

cPlayerGlobalState::cPlayerGlobalState()
{
}

cPlayerGlobalState::~cPlayerGlobalState()
{
}

void cPlayerGlobalState::EnterState(cGameObject * _entity)
{
}

void cPlayerGlobalState::ChangeState(cGameObject * _entity)
{

}

void cPlayerGlobalState::ExitState(cGameObject * _entity)
{
}

void cPlayerGlobalState::Execute(cGameObject * _entity)
{
	cStatus& status = _entity->GetStatus();
	if (1 > status.GetCurrentHP())
	{

	}
	else
	{

	}
}

bool cPlayerGlobalState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	return false;
}
