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

void cAction::ReadyApproach(cGameObject * _pTarget,const float & _fTargetRange)
{
	m_pTarget = _pTarget;
	m_fTargetRange = _fTargetRange;

	static D3DXVECTOR3 vCurTo;
	vCurTo = m_pTarget->GetVPos();

	D3DXVECTOR3 vVolume = m_vFrom - vCurTo;
	D3DXVec3Normalize(&vVolume, &vVolume);
	vVolume *= m_fTargetRange;
	vVolume += vCurTo;
	m_vTo = vVolume;

	ReadyMoveTo(m_vTo);
}

void cAction::Approach()
{
	if (!m_bAction)
		return;
	/*
	m_vFrom = m_pOwner->GetVPos();
	m_vTo = m_pTarget->GetVPos();

	D3DXVECTOR3 velocity = m_vTo - m_vFrom;
	float		fDistance = D3DXVec3LengthSq(&velocity);

	D3DXVec3Normalize(&velocity, &velocity);
	velocity /= m_fSpeed;
	float		fMoveAmount = D3DXVec3LengthSq(&velocity);
	
	if (fDistance-(m_fTargetRange*m_fTargetRange) > fMoveAmount)
	{
		m_pOwner->SetVPos(m_vFrom + velocity);
		HeadTo();
	}
	else
	{
		if (m_pDelegate)
			m_pDelegate->OnActionDelegate(this);
		m_pOwner->SetVPos(m_vTo);
	}*/
	static D3DXVECTOR3 vPrevTo;
	static D3DXVECTOR3 vCurTo;
	vCurTo = m_pTarget->GetVPos();

	
	if (vPrevTo != vCurTo)
	{
		D3DXVECTOR3 vVolume = m_vFrom - vCurTo;
		D3DXVec3Normalize(&vVolume, &vVolume);
		vVolume *= m_fTargetRange;
		vVolume += vCurTo;
		m_vTo = vVolume;
		ReadyMoveTo(m_vTo);
		Start();
	}
	MoveTo();
	vPrevTo = vCurTo;
}

void cAction::ReadyAttack(cGameObject * _pTarget, const float& attackAniTime)
{
	m_fActionTime = attackAniTime;
}

void cAction::Attack()
{
	if (!m_bAction)
		return;
	m_fPassedTime += g_pTimeManager->GetDeltaTime();
	if (m_fPassedTime>m_fActionTime)
	{
		g_pMessageDispatcher->Dispatch(m_pOwner->GetID(), m_pTarget->GetID(), 0.0f, Msg_Hit, NULL);
		g_pMessageDispatcher->Dispatch(m_pTarget->GetID(), m_pOwner->GetID(), 0.0f, Msg_AttackTarget,NULL);
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
