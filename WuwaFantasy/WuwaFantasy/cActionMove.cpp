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
	cGameObject* pOwner = GetOwner();
	cStatus& status = pOwner->GetStatus();

	if (fActionTime <= 0.0f)
	{
		fActionTime = (D3DXVec3LengthSq(&(m_vTo-m_vFrom))+0.001f)/status.GetSpeed();
	}

	SetPassedTime(0.0f);

	D3DXVECTOR3 vTargetDir = m_vTo - m_vFrom;
	D3DXVec3Normalize(&vTargetDir, &vTargetDir);

	D3DXVECTOR3 vCurDir = pOwner->GetVDir();

	D3DXVECTOR3 vCurSideDir;

	D3DXVec3Cross(&vCurSideDir, &vCurDir, &D3DXVECTOR3(0, 1, 0));

	float f = D3DXVec3Dot(&vTargetDir, &vCurDir);
	float sf = D3DXVec3Dot(&vTargetDir, &vCurSideDir);

	float radian = (1.0f - f)*0.5f*D3DX_PI;

	if (f < sf)
	{
		pOwner->TurnRotationY(radian);
	}
	else
	{
		pOwner->TurnRotationY(-radian);
	}

	GetOwner()->SetVDir(vTargetDir);
}

void cActionMove::Update()
{
	if (!IsAction())
		return;

	float fPassedTime = GetPassedTime();
	float fActionTime = GetActionTime();
	
	if (fPassedTime < fActionTime)
	{
		fPassedTime += g_pTimeManager->GetDeltaTime();

		float t = GetPassedTime() / GetActionTime();
		D3DXVECTOR3 velocity = (1.0f - t) * m_vFrom + t * m_vTo;
		GetOwner()->SetVPos(velocity);
	}
	else
	{
		GetOwner()->SetVPos(m_vTo);
		if (GetDelegate())
			GetDelegate()->OnActionDelegate(this);
		SetAction(false);
	}
	
}
