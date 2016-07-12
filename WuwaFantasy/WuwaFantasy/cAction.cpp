#include "stdafx.h"
#include "cAction.h"
#include"cGameObject.h"
#include"cStatus.h"
#include "cRandom.h"
#include "cSkill.h"

cAction::cAction(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
	m_entityID = m_pOwner->GetID();
}

cAction::~cAction()
{
}

cGameObject * cAction::GetOwner()
{
	return m_pOwner;
}

void cAction::SetOwner(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
	m_entityID = m_pOwner->GetID();
}

cGameObject * cAction::GetTarget()
{
	return m_pTarget;
}

void cAction::SetTarget(cGameObject * _pTarget)
{
	m_pTarget = _pTarget;
}

void cAction::ReadyMoveTo(const D3DXVECTOR3 & _vTo)
{
	const cStatus& status = m_pOwner->GetStatus();
	m_vFrom = m_pOwner->GetVPos();
	m_vTo = _vTo;
	m_fActionTime = (D3DXVec3Length(&(m_vTo - m_vFrom)) + 0.001f) / (status.GetSpeed());

	HeadTo();
}

void cAction::MoveTo()
{
	if (!m_bAction)
		return;

	m_fPassedTime += g_pTimeManager->GetDeltaTime();

	if (m_fPassedTime < m_fActionTime)
	{
		float t = m_fPassedTime / m_fActionTime;
		D3DXVECTOR3 velocity = (1.0f - t) * m_vFrom + t * m_vTo;
		m_pOwner->SetVPos(velocity);
	}
	else
	{
		if(m_pOwner)
			m_pOwner->SetVPos(m_vTo);
		if (m_pDelegate)
			m_pDelegate->OnActionDelegate(this);
	}
}

void cAction::ReadyHeadTo(const D3DXVECTOR3 & _vTo)
{
	if (m_pOwner)
	{
		m_vFrom = m_pOwner->GetVPos();
		m_vTo = _vTo;
	}
}

void cAction::HeadTo()
{
	if (m_pOwner)
	{
		D3DXVECTOR3 vTargetDir = m_vTo - m_vFrom;

		m_pOwner->SetVDir(vTargetDir);
	}
}

void cAction::ReadyPatrol(const D3DXVECTOR3 & _vCenter)
{
	m_sphere.fRadius = 5.0f;
	m_sphere.vCenter = _vCenter;
	m_fPassedTime = cRandom::GetFloat(m_fPatrolTime,0.0f);
}

void cAction::Patrol()
{
	if (!m_bAction)
		return;
	
	if (m_fPassedTime>m_fPatrolTime)
	{
		D3DXVECTOR3 velocity=D3DXVECTOR3(0,0,0);
		cRandom::GetVectorInCircle(velocity, m_sphere.fRadius);
		ReadyMoveTo(m_sphere.vCenter+velocity);
		m_fPassedTime = 0.0f;
		g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_MoveAni,NULL);
	}
	MoveTo();
}

void cAction::ReadyAttack(cSkill * _pSkill)
{
	if (m_pSkill)
		m_pSkill->Stop();
	m_pSkill = _pSkill;
	if (!m_pTarget)
	{
		m_pTarget = m_pOwner;
	}
	m_pSkill->SetTarget(m_pTarget);
	ReadyMoveTo(m_pTarget->GetVPos());
	m_fTargetRange = m_pSkill->GetDistance();
	m_bSkillStart = false;	
}

void cAction::Attack()
{
	if (!m_bAction||!m_pTarget)
		return;

	if (!m_bSkillStart)
	{
		D3DXVECTOR3 vLength = m_pTarget->GetVPos() - m_pOwner->GetVPos();
		float distance = D3DXVec3LengthSq(&vLength);
		m_pOwner->SetVDir(vLength);

		if (distance > m_fTargetRange*m_fTargetRange)
		{
			if (m_vTo != m_pTarget->GetVPos())
			{
				ReadyMoveTo(m_pTarget->GetVPos());
				Start();
			}
			g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_MoveAni,NULL);
			MoveTo();
		}
		else
		{
			m_pSkill->Start();
			m_bSkillStart = true;
		}
	}
}

void cAction::ReadyStun(const float & _stunTime)
{
	m_fActionTime = _stunTime;
}

void cAction::Stun()
{
	m_fPassedTime += g_pTimeManager->GetDeltaTime();
	if (m_fPassedTime > m_fActionTime)
		if (m_pDelegate)
			m_pDelegate->OnActionDelegate(this);
}

void cAction::OnSkillDelegate(cSkill * _pSender)
{
	m_bSkillStart = false;
	m_pSkill->Stop();
	if (m_pDelegate)
		m_pDelegate->OnActionDelegate(this);
}

void cAction::Start()
{
	m_bAction = true;
	m_fPassedTime = 0.0f;
}

void cAction::Stop()
{
	m_bAction = false;
}

void cAction::SetDelegate(cActionDelegate * _pDelegate)
{
	m_pDelegate = _pDelegate;
}

void cAction::SetFrom(const D3DXVECTOR3 & _from)
{
	m_vFrom = _from;
}

void cAction::SetTo(const D3DXVECTOR3 & _to)
{
	m_vTo = _to;
}

void cAction::SetActionTime(const float & _actiontime)
{
	m_fActionTime = _actiontime;
}
