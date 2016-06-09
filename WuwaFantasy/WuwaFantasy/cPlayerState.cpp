#include "stdafx.h"
#include "cPlayerState.h"
#include "cGameObject.h"

cPlayerState::cPlayerState(cIState* _state)
	:m_pState(_state)
{
}


cPlayerState::~cPlayerState()
{
}

void cPlayerState::EnterState(cGameObject * _entity)
{
	m_vecSkill.resize(10);
	ZeroMemory(&m_packet, sizeof(m_packet));
	m_pState->EnterState(_entity);
}

void cPlayerState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
}

void cPlayerState::Execute(cGameObject * _entity)
{
	m_pState->Execute(_entity);
}

bool cPlayerState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case  Msg_Skill:
		packet_skill = (Packet_Skill*)_packet.info;
		if (0 <= packet_skill->skill &&
			packet_skill->skill < SKILL_MAXNUM)
		{
			m_packet.msg_type = Msg_CastingAni;
			m_pState->OnMessage(_entity,m_packet);
		}
		SAFE_DELETE(packet_skill);
		break;
	default:
		return m_pState->OnMessage(_entity,_packet);
	}
	return false;
}
