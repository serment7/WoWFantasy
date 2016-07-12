#pragma once
#include "cSkill.h"

class cCondition;

class cImmediatelyHeal :
	public cSkill
{
private:
	Packet_AddCondition*			packet_condition = nullptr;

 	float							m_fCastTime = 1.0f;
	float							m_fPassedCastTime=0.0f;
public:
	cImmediatelyHeal(cGameObject* _pOwner);
	virtual ~cImmediatelyHeal();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
	virtual bool		CanUse();
};

