#pragma once
#include "cSkill.h"

class cBerserk :
	public cSkill
{
private:		
	float					m_fPassedTime = 0.0f;
	float					m_fAniTime = 0.0f;

	Packet_AddCondition*	packet_condition = nullptr;;
public:
	cBerserk(cGameObject* _pOwner,const float& _AniTime);
	virtual ~cBerserk();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
};

