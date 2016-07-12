#include "stdafx.h"
#include "cScorpionState.h"
#include "cGameObject.h"
#include "cBaseShortAttack.h"

cScorpionState::cScorpionState()
{
}

cScorpionState::~cScorpionState()
{
}

void cScorpionState::EnterState(cGameObject * _entity)
{
	m_pOwner = _entity;
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "scorpion");
	m_pOwner->GetChrSkinnedMesh()->Load("scorpion.X");
	m_entityID = _entity->GetID();

	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	SetupAnimation(1);

	_entity->SetBoundSphere(1, D3DXVECTOR3(0, 0, 0));

	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(0);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity,1.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);
}

void cScorpionState::ExitState(cGameObject * _entity)
{
}

void cScorpionState::Execute(cGameObject * _entity)
{
	m_pAniController->GetTrackDesc(0, &m_desc);
	m_fPassedAnitime += g_pTimeManager->GetDeltaTime();
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

bool cScorpionState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Death:
		SetupAnimation(2);
		m_bLive = false;
		m_bAttack = false;
		m_fPassedAnitime = 0.0f;
		return true;
	case Msg_IdleAni:
		SetupAnimation(1);
		m_bLive = true;
		return true;
	case Msg_MoveAni:
		SetupAnimation(6);
		return true;
	case Msg_AttackAni:
		SetupAnimation(0);
		if (m_bAttack)
			return true;
		m_bAttack = true;
		m_fPassedAnitime = 0.0f;
		return true;
	}
	return false;
}
