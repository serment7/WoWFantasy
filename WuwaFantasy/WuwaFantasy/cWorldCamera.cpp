#include "stdafx.h"
#include "cWorldCamera.h"


cWorldCamera::cWorldCamera()
{
}


cWorldCamera::~cWorldCamera()
{
}

void cWorldCamera::Update()
{
	D3DXMATRIXA16 matY;
	D3DXMatrixRotationY(&matY, D3DXToRadian( GetAngleY()));
	if (g_pKeyManager->isStayKeyDown('W'))
	{
		D3DXVECTOR3 velocity = D3DXVECTOR3(0, 0, m_fSpeed);
		D3DXVec3TransformCoord(&velocity,&velocity,&matY);
		MoveEye(velocity);
		MoveLookAt(velocity);
	}
	if (g_pKeyManager->isStayKeyDown('S'))
	{
		D3DXVECTOR3 velocity = D3DXVECTOR3(0, 0, -m_fSpeed);
		D3DXVec3TransformCoord(&velocity, &velocity, &matY);
		MoveEye(velocity);
		MoveLookAt(velocity);
	}
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		D3DXVECTOR3 velocity = D3DXVECTOR3(-m_fSpeed, 0, 0);
		D3DXVec3TransformCoord(&velocity, &velocity, &matY);
		MoveEye(velocity);
		MoveLookAt(velocity);
	}
	if (g_pKeyManager->isStayKeyDown('D'))
	{
		D3DXVECTOR3 velocity = D3DXVECTOR3(m_fSpeed, 0, 0);
		D3DXVec3TransformCoord(&velocity, &velocity, &matY);
		MoveEye(velocity);
		MoveLookAt(velocity);
	}
	cCamera::Update();
}
