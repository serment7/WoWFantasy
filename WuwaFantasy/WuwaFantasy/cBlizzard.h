#pragma once
#include "cSkill.h"
class cBlizzard :
	public cSkill
{
private:
	D3DXVECTOR3			m_vPos;
	D3DXMATRIXA16		m_matWorld;

	Packet_AddCondition*		packet_condition = nullptr;

	float				m_fRunTime = 12.0f;
	float				m_fPassedTime = 0.0f;

	float				m_fPerHitTime = 1.0f;
	float				m_fNextHitTime = 0.0f;

	std::vector<size_t>	m_vecTargetTag;
	BoundingSphere		m_skillRange;

	Packet_Hit*			packet_hit = nullptr;

public:
	cBlizzard(cGameObject* _pOwner, const float& _distance);
	virtual ~cBlizzard();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

