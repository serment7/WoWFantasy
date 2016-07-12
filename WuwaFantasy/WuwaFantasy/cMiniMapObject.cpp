#include "StdAfx.h"
#include "cMiniMapObject.h"

cMiniMapObject::cMiniMapObject(void)
	: m_pParent(NULL)
	, m_vPosition(0, 0, 0)
	, m_isDebugRender(true)
	, m_nTag(0)
{
	AddRef();
	D3DXMatrixIdentity(&m_matWorld);
}


cMiniMapObject::~cMiniMapObject(void)
{
}

void cMiniMapObject::AddChild(cMiniMapObject* pChild)
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cMiniMapObject::Update()
{
	UpdateWorldTM();
	UpdateChildren();
}

void cMiniMapObject::Render(LPD3DXSPRITE pSprite)
{
	for each(auto p in m_vecChild)
	{
		p->Render(pSprite);
	}
}

void cMiniMapObject::Destroy()
{
	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
	Release();
}

void cMiniMapObject::UpdateWorldTM()
{
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (m_pParent)
	{
		m_matWorld._41 += m_pParent->m_vPosition.x;
		m_matWorld._42 += m_pParent->m_vPosition.y;
		m_matWorld._43 += m_pParent->m_vPosition.z;
	}
}

void cMiniMapObject::UpdateChildren()
{
	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

cMiniMapObject* cMiniMapObject::GetChildByTag(int nTag)
{
	if (m_nTag == nTag)
		return this;
	for each(auto p in m_vecChild)
	{
		cMiniMapObject* pChild = p->GetChildByTag(nTag);

		if (pChild)
			return pChild;
	}
	return NULL;
}

