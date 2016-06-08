#include "stdafx.h"
#include "cAction.h"
#include"cGameObject.h"
#include"cStatus.h"

cAction::cAction(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
}

cAction::~cAction()
{
}

cGameObject * cAction::GetOwner()
{
	return m_pOwner;
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

	if (m_fPassedTime < m_fActionTime)
	{
		m_fPassedTime += g_pTimeManager->GetDeltaTime();

		float t = m_fPassedTime / m_fActionTime;
		D3DXVECTOR3 velocity = (1.0f - t) * m_vFrom + t * m_vTo;
		m_pOwner->SetVPos(velocity);
	}
	else
	{
		m_pOwner->SetVPos(m_vTo);
		if (m_pDelegate)
			m_pDelegate->OnActionDelegate(this);
	}
}

void cAction::ReadyHeadTo(const D3DXVECTOR3 & _vTo)
{
	m_vFrom = m_pOwner->GetVPos();
	m_vTo = _vTo;
}

void cAction::HeadTo()
{
	D3DXVECTOR3 vTargetDir = m_vTo - m_vFrom;
	m_pOwner->SetVDir(vTargetDir);
}

void cAction::ReadyApproach(const D3DXVECTOR3 & _vTo, const float & _fTargetRange)
{
	m_vFrom = m_pOwner->GetVPos();
	D3DXVECTOR3 vApproachTo = m_vFrom - _vTo;
	D3DXVec3Normalize(&vApproachTo, &vApproachTo);
	vApproachTo = _vTo - (vApproachTo * _fTargetRange);
	ReadyMoveTo(vApproachTo);
}

void cAction::Approach()
{
	MoveTo();
}

void cAction::ReadyAttack(cGameObject * _pTarget, const float & _attackRange)
{

}

void cAction::Attack()
{
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
