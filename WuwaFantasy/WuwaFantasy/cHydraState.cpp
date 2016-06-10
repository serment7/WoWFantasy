#include "stdafx.h"
#include "cHydraState.h"
#include "cGameObject.h"
#include "cRandom.h"

cHydraState::cHydraState()
{
}

cHydraState::~cHydraState()
{
}

void cHydraState::EnterState(cGameObject * _entity)
{
	m_pOwner = _entity;
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "Hydra");
	m_pOwner->GetChrSkinnedMesh()->Load("Hydra.X");

	
	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	cStatus* pStatus = &_entity->GetStatus();
	pStatus->SetSpeed(2.0f);
	pStatus->SetSenseRange(6.0f);
	pStatus->SetChaseRange(10.0f);
	m_chrmesh = _entity->GetChrSkinnedMesh();
	m_nCurAni = 3;
	SetupAnimation(m_nCurAni);
	
	_entity->SetBoundSphere(3, D3DXVECTOR3(0, 0, 0));
	m_pAniController->SetTrackPosition(0, cRandom::GetFloat(1.0f,0.0f));
}

void cHydraState::ExitState(cGameObject * _entity)
{
}

void cHydraState::Execute(cGameObject * _entity)
{
	if(!m_bLive)
	{
		m_pAniController->GetTrackDesc(0, &m_desc);
		m_fCurPeriod = m_pAniSet->GetPeriodicPosition(m_desc.Position) / m_fPeriod;
		
		if (m_desc.Position > m_fPeriod - 0.1f)
		{
			m_pAniController->SetTrackPosition(0, m_fPeriod - 0.1f);
		}
	}
	
}

bool cHydraState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_Death:
		m_nCurAni = 4;
		SetupAnimation(m_nCurAni);
		m_bLive = false;
		return true;
	case Msg_IdleAni:
		m_nCurAni = 3;
		SetupAnimation(m_nCurAni);
		return true;
	case Msg_MoveAni:
		m_nCurAni = 10;
		SetupAnimation(m_nCurAni);
		return true;
	case Msg_AttackAni:
		m_nCurAni = 7;
		SetupAnimation(m_nCurAni);
		return true;
	}
	return false;
}

void cHydraState::SetupAnimation(const int & index)
{
	m_pOwner->GetChrSkinnedMesh()->SetAnimationIndexBlend(m_nCurAni);
	m_pAniController->GetAnimationSet(m_nCurAni, &m_pAniSet);
	m_fPeriod = (float)m_pAniSet->GetPeriod();
	m_pAniController->SetTrackPosition(0, 0.0f);
}
