#pragma once

#include "cParticle.h"

class cGameObject;

class cThrownObject
	: public cParticle
{
private:
	cGameObject*			m_pOwner=nullptr;
	cGameObject*			m_pTarget = nullptr;
	cParticleDelgate*		m_pDelegate=nullptr;
	D3DXVECTOR3				m_vFrom;
	D3DXVECTOR3				m_vTo;
	D3DXVECTOR3				m_vPos;
	
	float					m_fRadius;
	float					m_fHeight;
public:
	cThrownObject(cGameObject* _pOwner, cGameObject* _pTarget, const float & _speed,
		cParticleDelgate* _delegate);
	cThrownObject(const float& _radius,const float& _startHeight,const float& _height, const float& _lifetime, bool _bRand,const DWORD& _color);
	~cThrownObject();

	virtual void Update(const float& _delta);
	virtual void Reset();
};

