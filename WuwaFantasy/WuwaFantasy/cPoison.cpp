#include "stdafx.h"
#include "cPoison.h"
#include "cGameObject.h"
//#include "cStatus.h"

cPoison::cPoison(const int & _nPerDamage, const float & _fPerHitTime, const float & _fConditionTime)
{
	m_nPerDamage = _nPerDamage;
	m_fHitTime = m_fPerHitTime = _fPerHitTime;
	m_fConditionTime = _fConditionTime;
}

cPoison::~cPoison()
{
}

void cPoison::Update()
{
	m_fPassedTime += g_pTimeManager->GetDeltaTime();
	if (m_fPassedTime > m_fHitTime)
	{
		cStatus& status = GetOwner()->GetStatus();
		status.DecCurrentHP(m_nPerDamage);
		m_fHitTime += m_fPerHitTime;
	}

	if (m_fPassedTime > m_fConditionTime)
	{
		delete this;
	}
}
