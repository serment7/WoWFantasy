#include "stdafx.h"
#include "cApproachState.h"
#include "cGameObject.h"
#include "cMoveState.h"
#include "cIdleState.h"

cApproachState::cApproachState()
{
}

cApproachState::~cApproachState()
{
}

void cApproachState::EnterState(cGameObject * _player)
{
	const size_t id = _player->GetID();
	m_pAction = _player->GetAction();
	m_pAction->SetDelegate(this);
	m_pAction = nullptr;
	g_pMessageDispatcher->Dispatch(id, id, 0.0f, Msg_MoveAni, NULL);
}

void cApproachState::ExitState(cGameObject * _player)
{
	m_pAction = _player->GetAction();
	m_pAction->SetDelegate(nullptr);
	m_pAction = nullptr;
}

void cApproachState::Execute(cGameObject * _player)
{	
	_player->GetAction()->Approach();
}

bool cApproachState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Approach:
		packet_target = (Packet_Target*)_packet.info;
		m_pAction = _player->GetAction();
		m_pTarget = packet_target->pTarget;
		m_pAction->Start();
		m_pAction->ReadyApproach(m_pTarget, _player->GetStatus().GetSpeed(),1);
		m_pTarget = nullptr;
		m_pAction = nullptr;
		SAFE_DELETE(packet_target);
		return true;
	case Msg_Move:
	case Msg_Idle:
	case Msg_Attack:
		return MessageCatch(_player, _packet);
	}

	return false;
}

void cApproachState::OnActionDelegate(cAction * _pSender)
{
	_pSender->Stop();
	_pSender->GetOwner()->GetStateMachine()->ChangeState(cIdleState::GetInstance());
}
