#pragma once
#include "cSkill.h"

class cFirePad :
	public cSkill
{
private:
	D3DXMATRIXA16		m_matWorld;

	float				m_fRunTime = 10.0f;
	float				m_fPassedTime = 0.0f;

	float				m_fPerHitTime = 1.0f;
	float				m_fNextHitTime = 0.0f;

	std::vector<size_t>	m_vecTargetTag;
	BoundingSphere		m_skillRange;

	Packet_Hit*			packet_hit = nullptr;

public:
	cFirePad(cGameObject* _pOwner, const float& _distance);
	virtual ~cFirePad();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

