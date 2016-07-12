#include "stdafx.h"
#include "cHumanWarriorState.h"
#include "cGameObject.h"
#include "cBaseShortAttack.h"
#include "cFirePad.h"
#include "cWound.h"
#include "cBerserk.h"

cHumanWarriorState::cHumanWarriorState()
{
}

cHumanWarriorState::~cHumanWarriorState()
{
}

void cHumanWarriorState::EnterState(cGameObject * _entity)
{
	_entity->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "HumanWarrior");
	_entity->GetChrSkinnedMesh()->Load("HumanWarrior.X");
	_entity->GetObjSkinnedMesh()->Load(std::string(MODEL_PATH + "twohandsword").c_str(), "twohandsword.X",  _entity->GetChrSkinnedMesh(), "RFingerRing");

	m_entityID = _entity->GetID();

	m_pOwner = _entity;

	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(9);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity, 1.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	fAttackPeriod = m_chrmesh->GetAnimationPeriod(5);
	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL1, new cBerserk(_entity, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL2, new cWound(_entity, 1.0f));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	SetupAnimation(15);
}

void cHumanWarriorState::ExitState(cGameObject * _entity)
{
}

void cHumanWarriorState::Execute(cGameObject * _entity)
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

bool cHumanWarriorState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Respawn:
		m_bLive = true;
		m_bAttack = false;
		return true;
	case Msg_BattleRoarAni:
		SetupAnimation(5);
		m_bAttack = true;
		return true;
	case Msg_WoundAni:
		SetupAnimation(4);
		m_bAttack = false;
		return true;
	case Msg_IdleAni:
		SetupAnimation(15);
		m_bAttack = false;
		return true;
	case Msg_MoveAni:
		SetupAnimation(24);
		m_bAttack = false;
		return true;
	case Msg_AttackAni:
		SetupAnimation(9);
		m_bAttack = true;
		return true;
	case Msg_CastingAni:
		SetupAnimation(17);
		m_bAttack = false;
		return true;
	case Msg_StunAni:
		SetupAnimation(20);
		m_bAttack = false;
		return true;
	case Msg_Death:
		SetupAnimation(21);
		m_bAttack = false;
		m_bLive = false;
		m_fPassedAnitime = 0.0f;
		return true;

	}
	return false;
}
