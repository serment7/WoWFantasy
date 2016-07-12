#pragma once
#include "cSkill.h"

class cFireHand :
	public cSkill
{
private:
	float					m_fPassedCastTime =0.0f;
	float					m_fEffectTiming=0.0f;
	float					m_fCastTime = 0.0f;

	bool					m_bEffect = false;

public:
	cFireHand(cGameObject* _pOwner, const float& _distance, const float& _fTiming,const float& _fCastTime);
	virtual ~cFireHand();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
	virtual bool		CanUse();
};

