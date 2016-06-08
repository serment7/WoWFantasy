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
	m_pAction = _player->GetAction();
	m_pAction->SetDelegate(this);
	m_pAction->Start();
	m_pAction = nullptr;
}

void cApproachState::ExitState(cGameObject * _player)
{
	m_pAction = _player->GetAction();
	m_pAction->SetDelegate(nullptr);
	m_pAction->Stop();
	m_pAction = nullptr;
}

void cApproachState::Execute(cGameObject * _player)
{
	m_pAction->Approach();
}

bool cApproachState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Approach:
		packet_target = (Packet_Target*)_packet.info;
		m_pAction = _player->GetAction();
		m_pTarget = packet_target->pTarget;
		m_pAction->ReadyApproach(m_pTarget->GetVPos(), m_pTarget->GetBoundSphere().fRadius);
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
