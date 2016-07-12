#pragma once
#include "cSkill.h"

class cGameObject;

class cCondition;

class cBattleRoar :
	public cSkill
{
private:
	Packet_AddCondition*			packet_condition = nullptr;
	D3DXVECTOR3						m_vPos;
	
	std::vector<size_t>				m_vecTargetTag;

	float							m_fPassedCastTime=0.0f;
	float							m_fEffectTiming=0.0f;
	float							m_fCastTime = 0.0f;
	float							m_fSkillEffectDistance = 10.0f;

	std::list<cGameObject*>			m_listTargets;

	bool							m_bEffect = false;
public:
	cBattleRoar(cGameObject* _pOwner, const float& _fDistance, const float& _fEffectTiming, const float& _fCastPeriod);
	virtual ~cBattleRoar();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

