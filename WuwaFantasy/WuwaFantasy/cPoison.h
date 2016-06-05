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

public:
	cPoison(const int& _nPerDamage,
		const float& _fPerHitTime,
		const float& _fConditionTime);
	virtual ~cPoison();

	virtual void Update();
};

