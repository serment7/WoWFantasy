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
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matRotX);
	D3DXMatrixIdentity(&m_matRotY);
	D3DXMatrixIdentity(&m_matWorld);
}

cCamera::~cCamera()
{
}

void cCamera::Update()
{
	m_vEye = D3DXVECTOR3(0, 0, -m_fDistance);
	D3DXMatrixRotationX(&m_matRotX, D3DXToRadian(m_fAngleX));
	D3DXMatrixRotationY(&m_matRotY, D3DXToRadian(m_fAngleY));
	D3DXMatrixTranslation(&m_matTrans, m_vPos.x,m_vPos.y, m_vPos.z);
	m_matWorld = m_matRotX*m_matRotY*m_matTrans;
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &m_matWorld);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFovy, m_fAspect, m_fMinFov, m_fMaxFov);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &m_matProj);
}

void cCamera::SetEye(const D3DXVECTOR3 & _vPos)
{
	m_vPos = _vPos;
}

void cCamera::MoveEye(const D3DXVECTOR3 & _vPos)
{
	m_vPos += _vPos;
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

void cCamera::MoveLookAt(const D3DXVECTOR3 & _vPos)
{
	m_vLookAt += _vPos;
}

const D3DXVECTOR3 & cCamera::GetEye()
{
	return m_vPos;
}

const D3DXVECTOR3 & cCamera::GetLookAt()
{
	return m_vLookAt;
}

void cCamera::SetAngleX(const float & _angleX)
{
	m_fAngleX = _angleX;
}

void cCamera::SetAngleY(const float & _angleY)
{
	m_fAngleY = _angleY;
}

void cCamera::MoveAngleX(const float & _angleX)
{
	m_fAngleX += _angleX;
}

void cCamera::MoveAngleY(const float & _angleY)
{
	m_fAngleX += _angleY;
}

const float & cCamera::GetAngleX()
{
	return m_fAngleX;
}

const float & cCamera::GetAngleY()
{
	return m_fAngleY;
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

void cCamera::SetDistance(const float & _distance)
{
	m_fDistance = _distance;
}

const float&  cCamera::GetDistance()
{
	return m_fDistance;
}

bool cCamera::MessageHandle(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		return true;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		return true;
	case WM_MOUSEMOVE:
	{
		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);
			m_fAngleX += (ptCurrMouse.y - m_ptPrevMouse.y);
			m_fAngleY += (ptCurrMouse.x - m_ptPrevMouse.x);
			m_ptPrevMouse = ptCurrMouse;
			if (m_fAngleX > 89)
			{
				m_fAngleX = 89;
			}
			else if (m_fAngleX < -89)
			{
				m_fAngleX = -89;
			}
			if (m_fAngleY > 360) 
			{
				m_fAngleY -= 360;
			}	
			else if (m_fAngleY < 0)
			{
				m_fAngleY += 360;
			}
		}
	}
	return true;
	case WM_MOUSEWHEEL:
		m_fDistance -= GET_WHEEL_DELTA_WPARAM(wParam) / 100.0f;
		if (m_fDistance < m_fMinDistance)
			m_fDistance = m_fMinDistance;
		return true;
	}
	return false;
}
