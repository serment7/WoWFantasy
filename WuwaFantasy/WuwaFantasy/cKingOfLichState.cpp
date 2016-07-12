#include "stdafx.h"
#include "cKingOfLichState.h"
#include "cGameObject.h"
#include "cRandom.h"
#include "cBlizzard.h"
#include "cBaseShortAttack.h"
#include "cBattleRoar.h"

cKingOfLichState::cKingOfLichState()
{
}


cKingOfLichState::~cKingOfLichState()
{
}

void cKingOfLichState::EnterState(cGameObject * _entity)
{
	m_pOwner = _entity;
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "TheKingOfLich");
	m_pOwner->GetChrSkinnedMesh()->Load("LichKingAratame.X");
	m_pOwner->SetScaling(3, 3, 3);
	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	SetupAnimation(3);

	m_entityID = _entity->GetID();

	std::vector<size_t> target;
	target.push_back(g_pGameManager->FindObjectType("player"));
	target.push_back(g_pGameManager->FindObjectType("combatnpc"));
	
	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(14);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity,2.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL1, new cBlizzard(m_pOwner,2.0f));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	fAttackPeriod = m_chrmesh->GetAnimationPeriod(13);
	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL2, new cBattleRoar(m_pOwner, 5.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);
}

void cKingOfLichState::ExitState(cGameObject * _entity)
{
}

void cKingOfLichState::Execute(cGameObject * _entity)
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


bool cKingOfLichState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	int randAni;
	switch (_packet.msg_type)
	{
	case Msg_IdleAni:
		SetupAnimation(3);
		m_bLive = true;
		return true;
	case Msg_MoveAni:
		SetupAnimation(5);
		return true;
	case Msg_AttackAni:
		randAni = cRandom::GetInteger(15,14);
		if (m_bAttack)
			return true;
		SetupAnimation(randAni);
		m_bAttack = true;
		m_fPassedAnitime = 0.0f;
		return true;
	case Msg_Death:
		SetupAnimation(8);
		m_bLive = false;
		return true;
	case Msg_StunAni:
		SetupAnimation(0);
		return true;
	case Msg_BattleRoarAni:
		SetupAnimation(13);
		return true;
	}
	return false;
}