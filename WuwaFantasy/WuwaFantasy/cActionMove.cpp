#include "stdafx.h"
#include "cActionMove.h"
#include "cGameObject.h"

cActionMove::cActionMove()
{
}

cActionMove::~cActionMove()
{
}

void cActionMove::SetFrom(const D3DXVECTOR3 & _vFrom)
{
	m_vFrom = _vFrom;
}

void cActionMove::SetTo(const D3DXVECTOR3 & _vTo)
{
	m_vTo = _vTo;
}

void cActionMove::Start()
{
	float fActionTime = GetActionTime();
	if (fActionTime <= 0.0f)
	{
		fActionTime = D3DXVec3LengthSq(&(m_vTo-m_vFrom));
	}
	SetPassedTime(0.0f);
	m_vCurPos = m_vFrom;

	D3DXVECTOR3 vDir = m_vTo - m_vFrom;
	D3DXVec3Normalize(&vDir, &vDir);
	GetOwner()->SetVDir(vDir);
}

void cActionMove::Update()
{
	float fPassedTime = GetPassedTime();
	float fActionTime = GetActionTime();
	
	if (fPassedTime < fActionTime)
	{
		fPassedTime += g_pTimeManager->GetDeltaTime();

		float t = GetPassedTime() / GetActionTime();
		D3DXVECTOR3 velocity = (1.0f - t) * m_vFrom + t * m_vTo;
		m_vCurPos += velocity;
		GetOwner()->SetVPos(m_vCurPos);
	}
	
}
