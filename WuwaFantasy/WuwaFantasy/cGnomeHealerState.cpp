#include "stdafx.h"
#include "cGnomeHealerState.h"
#include "cGameObject.h"
#include "cBaseShortAttack.h"
#include "cImmediatelyHeal.h"
#include "cBless.h"

cGnomeHealerState::cGnomeHealerState()
{
}


cGnomeHealerState::~cGnomeHealerState()
{
}

void cGnomeHealerState::EnterState(cGameObject * _entity)
{
	_entity->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "GnomeFemaleHealer");
	_entity->GetChrSkinnedMesh()->Load("GnomeFemaleHealer.X");
	_entity->GetObjSkinnedMesh()->Load(std::string(MODEL_PATH + "mace").c_str(), "mace.X",  _entity->GetChrSkinnedMesh(), "RFingerPinky");

	m_entityID = _entity->GetID();

	m_pOwner = _entity;

	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(6);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity, 1.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL1, new cImmediatelyHeal(_entity));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	fAttackPeriod = m_chrmesh->GetAnimationPeriod(12);
	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL2, new cBless(_entity, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	SetupAnimation(2);
}

void cGnomeHealerState::ExitState(cGameObject * _entity)
{
}

void cGnomeHealerState::Execute(cGameObject * _entity)
{
	m_pAniController->GetTrackDesc(0, &m_desc);
	m_fPassedAnitime += g_pTimeManager->GetDeltaTime();

	float f = m_fPassedAnitime / m_fCurPeriod;
	if (!m_bLive)
	{
		if (m_fPassedAnitime > m_fPeriod - 0.1f)
		{
			m_pAniController->SetTrackPosition(0, m_fPeriod - 0.1f);
		}
	}
	else if (m_bAttack)
	{
		if (m_fPassedAnitime > m_fPeriod - 0.1f)
		{
			m_pAniController->SetTrackPosition(0, 0.0f);
			m_bAttack = false;
		}
	}
}

bool cGnomeHealerState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Respawn:
		m_bLive = true;
		m_bAttack = false;
		return true;
	case Msg_IdleAni:
		SetupAnimation(2);
		m_bAttack = false;
		return true;
	case Msg_MoveAni:
		SetupAnimation(17);
		m_bAttack = false;
		return true;
	case Msg_AttackAni:
		SetupAnimation(6);
		m_bAttack = true;
		return true;
	case Msg_CastingAni:
		SetupAnimation(12);
		m_bAttack = false;
		return true;
	case Msg_StunAni:
		SetupAnimation(9);
		m_bAttack = false;
		return true;
	case Msg_Death:
		SetupAnimation(30);
		m_bAttack = false;
		m_bLive = false;
		m_fPassedAnitime = 0.0f;
		return true;
	}
	return false;
}
