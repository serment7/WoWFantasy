#pragma once
#include "cCondition.h"


class cPoison :
	public cCondition
{
private:
	float			m_fPassedTime = 0.0f;
	float			m_fHitTime = 0.0f;
	float			m_fPerHitTime = 0.0f;
	float			m_fConditionTime = 0.0f;

	int				m_nPerDamage = 0;

	BoundingSphere		m_skillRange;

	Packet_Hit*		packet_hit = nullptr;

	D3DXVECTOR3			m_vPos;
	D3DXMATRIXA16		m_matWorld;

public:
	cPoison(cGameObject* _pOwner,const int& _nPerDamage,
		const float& _fPerHitTime,
		const float& _fConditionTime);
	virtual ~cPoison();

	virtual void	Update(const float& _delta, bool& _lifeTime);
	virtual void	Render();
};

