#pragma once
#include "cCondition.h"

class cStatus;

class cIncATK :
	public cCondition
{
private:
	cStatus*		m_pOwnerStatus;
	int				m_nIncAttackDamage = 0;
	float			m_fPassedTime = 0.0f;
	float			m_fConditionTime = 0.0f;

	BoundingSphere		m_skillRange;

	D3DXVECTOR3			m_vPos;
	D3DXMATRIXA16		m_matWorld;
public:
	cIncATK(cGameObject* _pOwner,const int& _IncDamage,const float& _skilltime);
	virtual ~cIncATK();

	virtual void	Update(const float& _delta, bool& _lifeTime);
	virtual void	Render();
};

