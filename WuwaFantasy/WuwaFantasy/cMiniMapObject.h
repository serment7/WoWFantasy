#pragma once
#include "cObject.h"

class cMiniMapObject : public cObject
{
protected:
	std::vector<cMiniMapObject*> m_vecChild;
	D3DXMATRIXA16			m_matWorld;
	cMiniMapObject*				m_pParent;

	SYNTHESIZE(bool, m_isDebugRender, DebugRender);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	SYNTHESIZE(int, m_nTag, Tag);

public:
	cMiniMapObject(void);
	virtual ~cMiniMapObject(void);

	virtual void AddChild(cMiniMapObject* pChild);
	virtual void Update();
	virtual void UpdateWorldTM();
	virtual void UpdateChildren();
	virtual void Render(LPD3DXSPRITE pSprite);
	virtual void Destroy();
	virtual cMiniMapObject* GetChildByTag(int nTag);
};

