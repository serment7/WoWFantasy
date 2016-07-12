#include "StdAfx.h"
#include "cUIObject.h"


cUIObject::cUIObject(void)
	: m_pParent(NULL)
	, m_vPosition(0, 0, 0)
	, m_isDebugRender(true)
	, m_nTag(0)
{
	D3DXMatrixIdentity(&m_matWorld);
	AddRef();
}


cUIObject::~cUIObject(void)
{
}

void cUIObject::AddChild( cUIObject* pChild )
{
	pChild->m_pParent = this;
	m_vecChild.push_back(pChild);
}

void cUIObject::Update()
{
	UpdateWorldTM();
	UpdateChildren();
}

void cUIObject::Render( LPD3DXSPRITE pSprite )
{
	for each(auto p in m_vecChild)
	{
		p->Render(pSprite);
	}
}

void cUIObject::Destroy()
{
	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
	}
	Release();
}

void cUIObject::UpdateWorldTM()
{
	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if(m_pParent)
	{
		m_matWorld._41 += m_pParent->m_vPosition.x;
		m_matWorld._42 += m_pParent->m_vPosition.y;
		m_matWorld._43 += m_pParent->m_vPosition.z;
	}
}

void cUIObject::UpdateChildren()
{
	for each(auto p in m_vecChild)
	{
		p->Update();
	}
}

cUIObject* cUIObject::GetChildByTag( int nTag )
{
	if (m_nTag == nTag)
		return this;
	for each(auto p in m_vecChild)
	{
		cUIObject* pChild = p->GetChildByTag(nTag);

		if (pChild)
			return pChild;
	}
	return NULL;
}

void cUIObject::SetDepth(const float & _depth)
{
	m_fZDepth = _depth;
}

const float & cUIObject::GetDepth()
{
	return m_fZDepth;
}

