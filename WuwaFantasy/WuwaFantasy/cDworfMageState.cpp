#include "stdafx.h"
#include "cDworfMageState.h"
#include "cGameObject.h"

cDworfMageState::cDworfMageState()
{
}

cDworfMageState::~cDworfMageState()
{
}

void cDworfMageState::EnterState(cGameObject * _entity)
{
	_entity->GetChrSkinnedMesh()->SetAnimationIndexBlend(20);
}

void cDworfMageState::ExitState(cGameObject * _entity)
{
}

void cDworfMageState::Execute(cGameObject * _entity)
{
	cStatus& status = _entity->GetStatus();
	if (1 > status.GetCurrentHP())
	{

	}
	else
	{

	}
}

bool cDworfMageState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_IdleAni:
		_entity->GetChrSkinnedMesh()->SetAnimationIndexBlend(20);
		return true;
	case Msg_MoveAni:
		_entity->GetChrSkinnedMesh()->SetAnimationIndexBlend(34);
		return true;
	case Msg_AttackAni:
		_entity->GetChrSkinnedMesh()->SetAnimationIndexBlend(13);
		return true;
	}
	return false;
}