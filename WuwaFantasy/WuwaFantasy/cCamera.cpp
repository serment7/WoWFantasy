#include "stdafx.h"
#include "cCamera.h"


cCamera::cCamera()
	: m_vEye(0.0f, 0.0f, 0.0f)
	, m_vUp(0.0f, 1.0f, 0.0f)
	, m_vLookAt(0.0f, 0.0f, 0.0f)
	, m_fFovy(D3DX_PI / 4.0f)
{
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}

cCamera::~cCamera()
{
}

void cCamera::Update()
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);
	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovy, m_fAspect, m_fMinFov, m_fMaxFov);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCamera::SetEye(const D3DXVECTOR3 & _vPos)
{
	m_vEye = _vPos;
}

void cCamera::SetEye(const float & _x, const float & _y, const float & _z)
{
	SetEye(D3DXVECTOR3(_x, _y, _z));
}

void cCamera::SetLookAt(const D3DXVECTOR3 & _vLookAt)
{
	m_vLookAt = _vLookAt;
}

void cCamera::SetLookAt(const float & _x, const float & _y, const float & _z)
{
	SetLookAt(D3DXVECTOR3(_x, _y, _z));
}

void cCamera::SetFovy(const float & _fovy)
{
	m_fFovy = _fovy;
}

void cCamera::SetAspect(const float & _aspect)
{
	m_fAspect = _aspect;
}

void cCamera::SetMinFov(const float & _minFov)
{
	m_fMinFov = _minFov;
}

void cCamera::SetMaxFov(const float & _maxFov)
{
	m_fMaxFov = _maxFov;
}
