#pragma once
#include "cCondition.h"
class cHeal :
	public cCondition
{
private:
	float			m_fPassedTime = 0.0f;
	float			m_fHitTime = 0.0f;
	float			m_fPerHitTime = 0.0f;
	float			m_fConditionTime = 0.0f;

	int				m_nPerHeal = 0;

public:
	cHeal();
	~cHeal();

	virtual void Update();
};

