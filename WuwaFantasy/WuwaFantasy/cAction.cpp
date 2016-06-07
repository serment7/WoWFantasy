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

void cAction::ReadyMoveTo(const D3DXVECTOR3 & _vFrom, const D3DXVECTOR3 & _vTo)
{
	const cStatus& status = m_pOwner->GetStatus();
	m_vFrom = _vFrom;
	m_vTo = _vTo;
	m_fActionTime = (D3DXVec3Length(&(m_vTo - m_vFrom)) + 0.001f) / (status.GetSpeed());

	D3DXVECTOR3 vTargetDir = m_vTo - m_vFrom;
	m_pOwner->SetVDir(vTargetDir);
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
