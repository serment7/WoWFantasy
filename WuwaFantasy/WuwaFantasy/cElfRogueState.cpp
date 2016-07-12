#include "stdafx.h"
#include "cElfRogueState.h"
#include "cGameObject.h"
#include "cBaseThrowAttack.h"
#include "cPoisonKnife.h"
#include "cExplosionKnife.h"

cElfLogState::cElfLogState()
{
}


cElfLogState::~cElfLogState()
{
}

void cElfLogState::EnterState(cGameObject * _entity)
{
	_entity->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "log");
	_entity->GetChrSkinnedMesh()->Load("log.X");
	_entity->GetObjSkinnedMesh()->Load(std::string(MODEL_PATH + "knife").c_str(), "knife.X", _entity->GetChrSkinnedMesh(), "RFingerRing");  

	m_entityID = _entity->GetID();

	m_pOwner = _entity;

	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();


	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(11);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseThrowAttack(_entity, 10.0f, fAttackPeriod*0.7f, fAttackPeriod, new cGameObject(MODEL_PATH + "knife", "knife.X")));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL1, new cPoisonKnife(_entity, 10.0f, fAttackPeriod*0.7f, fAttackPeriod,new cGameObject(MODEL_PATH + "knife","knife.X")));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL2, new cExplosionKnife(_entity, 10.0f, fAttackPeriod*0.7f, fAttackPeriod, new cGameObject(MODEL_PATH + "knife", "knife.X")));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	SetupAnimation(20);

	
}

void cElfLogState::ExitState(cGameObject * _entity)
{
}

void cElfLogState::Execute(cGameObject * _entity)
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

bool cElfLogState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Respawn:
		m_bLive = true;
		m_bAttack = false;
		return true;
	case Msg_ThrowAni:
		SetupAnimation(11);
		m_bAttack = true;
		return true;
	case Msg_IdleAni:
		SetupAnimation(13);
		m_bAttack = false;
		return true;
	case Msg_MoveAni:
		SetupAnimation(26);
		m_bAttack = false;
		return true;
	case Msg_AttackAni:
		SetupAnimation(11);
		m_bAttack = true;
		m_fPassedAnitime = 0.0f;
		return true;
	case Msg_CastingAni:
		SetupAnimation(24);
		m_bAttack = false;
		return true;
	case Msg_StunAni:
		SetupAnimation(22);
		m_bAttack = false;
		return true;
	case Msg_Death:
		SetupAnimation(16);
		m_bAttack = false;
		m_bLive = false;
		m_fPassedAnitime = 0.0f;
		return true;
	}
	return false;
}
