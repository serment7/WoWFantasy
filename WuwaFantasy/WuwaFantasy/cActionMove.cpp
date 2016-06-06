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
	SetAction(true);
	float fActionTime = 0.0f;
	cGameObject* pOwner = GetOwner();
	cStatus& status = pOwner->GetStatus();

	fActionTime = (D3DXVec3Length(&(m_vTo - m_vFrom)) + 0.001f) / (status.GetSpeed());
	SetActionTime(fActionTime);

	SetPassedTime(0.0f);

	D3DXVECTOR3 vTargetDir = m_vTo - m_vFrom;
	D3DXVec3Normalize(&vTargetDir, &vTargetDir);
	vTargetDir.z = -vTargetDir.z;

	D3DXMATRIXA16 roty;
	D3DXMatrixRotationY(&roty, 1.0f*D3DX_PI);
	D3DXMATRIXA16 rot;
	D3DXMatrixLookAtLH(&rot, &D3DXVECTOR3(0, 0, 0), &vTargetDir, &D3DXVECTOR3(0, 1, 0));
	pOwner->SetRotationMatirx(rot);

	D3DXVECTOR3 vCurDir = pOwner->GetVDir();

	D3DXVECTOR3 vCurSideDir;

	D3DXVec3Cross(&vCurSideDir, &vCurDir, &D3DXVECTOR3(0, 1, 0));

	float f = D3DXVec3Dot(&vTargetDir, &vCurDir);
	float sf = D3DXVec3Dot(&vTargetDir, &vCurSideDir);

	float radian = (1.0f - f)*0.5f*D3DX_PI;

	if (0.0f < sf)
	{
		//pOwner->TurnRotationY(D3DXToDegree( -radian));
	}
	else
	{
		//pOwner->TurnRotationY(D3DXToDegree (radian));
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
		SetPassedTime(fPassedTime);

		float t = fPassedTime / fActionTime;
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

void cActionMove::Stop()
{
	SetAction(false);
}
