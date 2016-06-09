#include "stdafx.h"
#include "cHydraState.h"
#include "cGameObject.h"

cHydraState::cHydraState()
{
}

cHydraState::~cHydraState()
{
}

void cHydraState::EnterState(cGameObject * _entity)
{
	m_pOwner = _entity;
	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_pStatus = &_entity->GetStatus();
	m_chrmesh = _entity->GetChrSkinnedMesh();
	m_nCurAni = 3;
	SetupAnimation(3);
}

void cHydraState::ExitState(cGameObject * _entity)
{
}

void cHydraState::Execute(cGameObject * _entity)
{
	m_pAniController->GetTrackDesc(0, &m_desc);
	m_fCurPeriod = m_pAniSet->GetPeriodicPosition(m_desc.Position)/m_fPeriod;
	int HP = m_pStatus->GetMaxHP();

	if (m_bLive)
	{
		if (0 < HP)
		{
		}
		else
		{
			/*m_nCurAni = 4;
			SetupAnimation(m_nCurAni);
			m_bLive = false;*/
		}
	}
	else
	{
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
}
