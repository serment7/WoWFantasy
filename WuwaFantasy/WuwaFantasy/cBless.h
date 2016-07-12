#pragma once
#include "cSkill.h"
class cBless :
	public cSkill
{
private:
	float					m_fPassedTime = 0.0f;
	float					m_fAniTime = 0.0f;

	Packet_AddCondition*	packet_condition = nullptr;
public:
	cBless(cGameObject* _pOwner, const float& _AniTime);
	virtual ~cBless();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

