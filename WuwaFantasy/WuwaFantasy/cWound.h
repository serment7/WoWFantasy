#pragma once
#include "cSkill.h"
class cWound :
	public cSkill
{
private:
	D3DXVECTOR3				m_vPos;
	float					m_fPassedTime = 0.0f;
	float					m_fSkillTime = 5.0f;

	float					m_fAttackTiming = 0.0f;
	float					m_fPerAttack = 1.0f;

	float					m_fSkillEffectDistance = 2.0f;

	std::vector<size_t>				m_vecTargetTag;
	std::list<cGameObject*>			m_listTargets;

	Packet_Hit*				packet_hit = nullptr;
public:
	cWound(cGameObject* _pOwner, const float& _distance);
	virtual ~cWound();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

