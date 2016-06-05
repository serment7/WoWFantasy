#include "stdafx.h"
#include "cPlayerControlState.h"
#include"cActionMove.h"
#include"cPlayer.h"
#include"cActionMove.h"

cPlayerControlState::cPlayerControlState()
{
	m_actionMove = new cActionMove;
	m_actionMove->SetDelegate(this);
}


cPlayerControlState::~cPlayerControlState()
{
	SAFE_DELETE(m_actionMove);
}

void cPlayerControlState::EnterState(cGameObject * _player)
{
	m_actionMove->SetOwner(_player);
}

void cPlayerControlState::ChangeState(cGameObject * _player)
{
}

void cPlayerControlState::ExitState(cGameObject * _player)
{
}

void cPlayerControlState::Execute(cGameObject * _player)
{
	m_actionMove->Update();
}

bool cPlayerControlState::OnMessage(cGameObject * _player, const ST_PACKET & _packet)
{
	if (_packet.receiver != _player->GetID())
		return false;

	switch (_packet.msg_type)
	{
	case Msg_Attack:
		return true;
	case Msg_Move:
		Packet_Move* packet = (Packet_Move*)_packet.info;
		
		m_actionMove->SetFrom(_player->GetVPos());
		m_actionMove->SetTo(packet->vDes);
		m_actionMove->Start();
		SAFE_DELETE(packet);
		return true;
	}

	return false;
}

void cPlayerControlState::OnActionDelegate(cIAction * _pSender)
{
	m_actionMove->Stop();
}
