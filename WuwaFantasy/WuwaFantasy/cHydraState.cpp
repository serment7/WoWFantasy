#include "stdafx.h"
#include "cHydraState.h"
#include "cGameObject.h"
#include "cRandom.h"
#include "cBaseShortAttack.h"

cHydraState::cHydraState()
{
}

cHydraState::~cHydraState()
{
}

void cHydraState::EnterState(cGameObject * _entity)
{
	m_pOwner = _entity;
	m_entityID = _entity->GetID();
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "Hydra");
	m_pOwner->GetChrSkinnedMesh()->Load("Hydra.X");
	
	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	_entity->SetBoundSphere(3, D3DXVECTOR3(0, 0, 0));
	m_pAniController->SetTrackPosition(0, cRandom::GetFloat(1.0f,0.0f));

	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(7);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity,1.0f, fAttackPeriod*0.8f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	
}

void cHydraState::ExitState(cGameObject * _entity)
{
}

void cHydraState::Execute(cGameObject * _entity)
{
	m_pAniController->GetTrackDesc(0, &m_desc);
	m_fPassedAnitime += g_pTimeManager->GetDeltaTime();
	if(!m_bLive)
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

bool cHydraState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Death:
		SetupAnimation(4);
		m_bLive = false;
		m_bAttack = false;
		m_fPassedAnitime = 0.0f;
		return true;
	case Msg_IdleAni:
		SetupAnimation(3);
		m_bLive = true;
		return true;
	case Msg_MoveAni:
		SetupAnimation(10);
		return true;
	case Msg_AttackAni:
		SetupAnimation(7);
		if (m_bAttack)
			return true;
		m_bAttack = true;
		m_fPassedAnitime = 0.0f;
		//g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, m_fPeriod, Msg_Attack, NULL);
		return true;
	}
	return false;
}