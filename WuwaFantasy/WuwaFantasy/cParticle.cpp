#include "stdafx.h"
#include "cParticle.h"

inline DWORD FloatToDword(const float& _float) { return *(DWORD*)&_float; }

cParticle::cParticle()
{
}


cParticle::~cParticle()
{
}

void cParticle::Update(const float& _delta)
{
	m_fAge += _delta;
	D3DXVec3Normalize(&m_vDir, &m_vDir);
}

void cParticle::PreRender(const float& _fSize)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FloatToDword(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FloatToDword(_fSize));

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FloatToDword(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FloatToDword(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FloatToDword(1.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//z-buffer 읽기만 하고 쓰기는 금지
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetFVF(FVF);
}

void cParticle::PostRender()
{
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void cParticle::Reset()
{	
	m_fAge=int(m_fAge*100.0f) % int(m_fLifeTime*100.0f)/100.0f;
	SetLive(true);
}

void cParticle::SetPos(const D3DXVECTOR3 & _vPos)
{
	m_vPos = _vPos;
}

void cParticle::SetPos(const float & _x, const float & _y, const float & _z)
{
	SetPos(D3DXVECTOR3(_x, _y, _z));
}

void cParticle::MovePos(const D3DXVECTOR3 & vPos)
{
	m_vPos += vPos;
}

void cParticle::SetDir(const D3DXVECTOR3 & _vDir)
{
	m_vDir = _vDir;
}

void cParticle::SetDir(const float & _x, const float & _y, const float & _z)
{
	SetDir(D3DXVECTOR3(_x, _y, _z));
}

void cParticle::SetSize(const float & _size)
{
	m_fPointSize = _size;
}

void cParticle::SetSpeed(const float & _speed)
{
	m_fSpeed = _speed;
}

void cParticle::SetAge(const float & _age)
{
	m_fAge = _age;
}

void cParticle::SetLifeTime(const float & _lifetime)
{
	m_fLifeTime = _lifetime;
}

void cParticle::SetColor(const D3DXCOLOR & _color)
{
	m_color = _color;
}

const D3DCOLOR & cParticle::GetColor()
{
	return m_color;
}

void cParticle::SetLive(const bool & _isLive)
{
	m_bIsAlive = _isLive;
}

const D3DXVECTOR3 & cParticle::GetPos()
{
	return m_vPos;
}

const D3DXVECTOR3 & cParticle::GetDir()
{
	return m_vDir;
}

const float & cParticle::GetSize()
{
	return m_fPointSize;
}

const float & cParticle::GetSpeed()
{
	return m_fSpeed;
}

bool cParticle::IsLive()
{
	return m_bIsAlive;
}

const float & cParticle::GetAge()
{
	return m_fAge;
}

const float & cParticle::GetLifeTime()
{
	return m_fLifeTime;
}

void cParticle::SetRecycle(const bool & _isRecycle)
{
	m_bRecycle = _isRecycle;
}

bool cParticle::IsRecycle()
{
	return m_bRecycle;
}

void cParticle::SetShow(const bool & _bIsShow)
{
	m_bShow = _bIsShow;
}

bool cParticle::IsShow()
{
	return m_bShow;
}
