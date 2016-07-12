#include "stdafx.h"
#include "cIdleState.h"
#include "cGameObject.h"
#include "cAction.h"

cIdleState::cIdleState()
{
}

cIdleState::~cIdleState()
{
}

void cIdleState::EnterState(cGameObject * _player)
{
	size_t id = _player->GetID();
	g_pMessageDispatcher->Dispatch(id, id, 0.0f, Msg_IdleAni, NULL);
}

void cIdleState::ExitState(cGameObject * _player)
{
}

void cIdleState::Execute(cGameObject * _player)
{
}

bool cIdleState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Idle:
		_player->GetAction()->Stop();
		_player->GetAction()->SetDelegate(nullptr);
		return true;
	default:
		return MessageCatch(_player, _packet);
	}

	return false;
}
