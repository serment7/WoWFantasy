#pragma once
#include "cSkill.h"
class cBaseShortAttack :
	public cSkill
{
private:
	float				m_fAttackTiming=0.0f;
	float				m_fAttackPeriod=0.0f;

	Packet_Hit*			packet_hit=nullptr;

	float				m_fPassedTime = 0.0f;
	bool				m_bAttack=false;

public:
	cBaseShortAttack(cGameObject* _pOwner,const float& _skilldistance,const float& _attackTiming, const float& _attackPeriod);
	virtual ~cBaseShortAttack();

	virtual void Start();
	virtual void Update(const float& _delta);
	virtual void Render();
	virtual void Stop();
	virtual bool CanUse();
};

