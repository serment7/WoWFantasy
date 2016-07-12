#include "stdafx.h"
#include "cPatrolState.h"
#include "cGameObject.h"
#include "cAction.h"

cPatrolState::cPatrolState()
{
}


cPatrolState::~cPatrolState()
{
}

void cPatrolState::EnterState(cGameObject * _player)
{
}

void cPatrolState::ExitState(cGameObject * _player)
{
	m_pAction = _player->GetAction();
	m_pAction->SetDelegate(nullptr);
	m_pAction->Stop();
	m_pAction = nullptr;
}

void cPatrolState::Execute(cGameObject * _player)
{
	_player->GetAction()->Patrol();
}

bool cPatrolState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Patrol:
		packet_pos = (Packet_Pos*)_packet.info;
		m_pAction = _player->GetAction();
		m_pAction->SetOwner(_player);
		m_pAction->SetFrom(_player->GetVPos());
		m_pAction->SetTo(_player->GetVPos());
		m_pAction->ReadyPatrol(packet_pos->vPos);
		g_pMessageDispatcher->Dispatch(0,_player->GetID(),0.0f,Msg_IdleAni,NULL);
		m_pAction->SetDelegate(this);
		m_pAction->Start();
		m_pAction = nullptr;
		SAFE_DELETE(packet_pos);
		return true;
	default:
		MessageCatch(_player,_packet);
	}
	return false;
}

void cPatrolState::OnActionDelegate(cAction * _pSender)
{
	g_pMessageDispatcher->Dispatch(0,_pSender->GetOwner()->GetID(),0.0f,Msg_IdleAni,NULL);
}
