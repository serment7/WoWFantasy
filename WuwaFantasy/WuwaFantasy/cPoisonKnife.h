#pragma once
#include "cSkill.h"
#include "cAction.h"

class cGameObject;

class cPoisonKnife :
	public cSkill, public cActionDelegate
{
private:
	float					m_fPassedTime = 0.0f;
	float					m_fAttackTiming = 0.0f;
	float					m_fAniTime = 0.0f;

	bool					m_bAttack = false;

	cGameObject*			m_pThrown = nullptr;
	Packet_AddCondition*	packet_condition = nullptr;

	float					m_fAngleY = 0.0f;
public:
	cPoisonKnife(cGameObject* _pOwner, const float& _distance, const float& _attackTiming, const float& _fAniTime, cGameObject* _pThrown);
	virtual ~cPoisonKnife();

	virtual void		Start();
	virtual void		Update(const float& _delta);
	virtual void		Render();
	virtual void		Stop();
	virtual bool		CanUse();
	virtual void		OnActionDelegate(cAction* _pSender) override;
};

