#include "stdafx.h"
#include "cObject.h"
#include "cStateMachine.h"
#include"cCondition.h"
#include "cMap.h"

cObject::cObject()
	: m_vPos(0, 0, 0)
	, m_vDir(0, 0, 1)
	, m_vScale(1, 1, 1)
{
	D3DXMatrixIdentity(&m_matR);
}

cObject::~cObject()
{
	assert(nRefCount>=0&&"∞¥√º º“∏ÅE?ø©∑ØπÅE¿œæ˚œ™∞˙‹÷Ω¿¥œ¥Ÿ");
}

void cObject::Update()
{
	D3DXMatrixScaling(&m_matS, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXVec3Normalize(&m_vBaseDir, &m_vBaseDir);
	D3DXVec3Normalize(&m_vDir, &m_vDir);

	D3DXVECTOR3 vCurSideDir;

	D3DXVec3Cross(&vCurSideDir, &m_vBaseDir, &D3DXVECTOR3(0, 1, 0));

	float f = D3DXVec3Dot(&m_vBaseDir, &m_vDir);
	float sf = D3DXVec3Dot(&vCurSideDir, &m_vDir);

	float radian = (1.0f - f)*0.5f*D3DX_PI;

	if (0.0f < sf)
	{
		m_fAngleY = -radian;
	}
	else
	{
		m_fAngleY = radian;
	}

	D3DXMatrixRotationY(&m_matR, m_fAngleY);

	std::vector<cMap*>& maps = g_pGameManager->GetMap();
	for (size_t i = 0; i < maps.size(); ++i)
	{
		if (maps[i]->CalcHeight(m_vPos.x, m_vPos.y, m_vPos.z))
			break;
	}

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	m_matWorld = m_matS * m_matR * m_matT;

	if (m_fAngleY > 360)
	{
		m_fAngleY -= 360;
	}
	else if (m_fAngleY < 0)
	{
		m_fAngleY += 360;
	}
}

const float & cObject::GetRotationY() const
{
	return m_fAngleY;
}
