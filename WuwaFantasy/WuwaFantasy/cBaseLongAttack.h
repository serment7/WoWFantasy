#pragma once
#include "cSkill.h"
#include "cParticle.h"

class cBaseLongAttack :
	public cSkill, public cParticleDelgate
{
private:
	size_t				m_entityID=MAXSIZE_T;
	size_t				m_targetID= MAXSIZE_T;

	Packet_Hit*			packet_hit;

	D3DXVECTOR3			m_vFrom;
	D3DXVECTOR3			m_vTo;

	D3DXVECTOR3			targetpos;
	D3DXVECTOR3			curPos;

	int					m_nThrownObject = 0;

	float				m_fAttackPeriod=0.0f;
	float				m_fAttackTiming = 0.0f;
	float				m_fPassedTime = 0.0f;
	bool				m_bShoot = false;

public:
	cBaseLongAttack(const float& _distance, 
		const float& _attackTiming,
		const float& _attackPeriod,
		const std::string& _throwntexture);

	virtual ~cBaseLongAttack();

	virtual void Start();
	virtual void Update(const float& _delta);
	virtual void Render();
	virtual void Stop();
	virtual void OnParticleDelegate(cParticle* _pSender);
	virtual bool CanUse();
};

