#pragma once
#include "cCondition.h"

class cStatus;

class cHeal :
	public cCondition
{
private:
	float			m_fPassedTime = 0.0f;
	float			m_fHealTime = 0.0f;
	float			m_fPerHealTime = 0.0f;
	float			m_fConditionTime = 0.0f;

	int				m_nNumHeal = 0;
	int				m_nHealAmount = 0;

	cStatus*		m_pTargetStatus = nullptr;

	D3DXVECTOR3		m_vecOwner;
	D3DXMATRIXA16	m_matWorld;

public:
	cHeal(cGameObject* _pTarget, const int& _nHealAmount,const float& _fPerHealTime, const float& _HealNum);
	virtual ~cHeal();

	virtual void	Update(const float& _delta, bool& _lifeTime);
	virtual void	PostRender();
};

