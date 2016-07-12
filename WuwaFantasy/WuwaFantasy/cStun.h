#pragma once
#include "cCondition.h"

class cParticleEffect;

class cStun :
	public cCondition
{
private:
	size_t				m_entityID=MAXSIZE_T;
	float				m_fPassedTime=0.0f;
	float				m_fStunTime=0.0f;
	
	D3DXMATRIXA16		m_trans;

public:
	cStun(cGameObject* _pOwner, const float& _fStunTime);
	virtual ~cStun();

	virtual void	Update(const float& _delta, bool& _lifeTime);
	virtual void	PostRender();
};

