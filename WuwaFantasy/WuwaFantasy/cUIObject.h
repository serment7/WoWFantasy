#pragma once

#include "cObject.h"

class cUIObject : public cObject
{
protected:
	std::vector<cUIObject*> m_vecChild;
	D3DXMATRIXA16			m_matWorld;
	cUIObject*				m_pParent;
	float					m_fZDepth=0.0f;

	SYNTHESIZE(D3DXVECTOR3, m_vCenter, Center);
	SYNTHESIZE(bool, m_isDebugRender, DebugRender);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	cUIObject(void);
	virtual ~cUIObject(void);

	virtual void AddChild(cUIObject* pChild);
	virtual void Update();
	virtual void UpdateWorldTM();
	virtual void UpdateChildren();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual cUIObject* GetChildByTag(int nTag);
	void SetDepth(const float& _depth);
	const float& GetDepth();
};

