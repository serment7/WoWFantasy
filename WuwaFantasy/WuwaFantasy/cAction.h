#pragma once
#include "cSkill.h"

class cGameObject;
class cAction;

class cActionDelegate
{
public:
	virtual void OnActionDelegate(cAction* _pSender) = 0;
};

class cAction
	: public cSklilDelegate
{
private:
	cGameObject*			m_pOwner = nullptr;
	cGameObject*			m_pTarget = nullptr;
	size_t					m_entityID = -1;
	cActionDelegate*		m_pDelegate = nullptr;

	float					m_fPassedTime = 0.0f;
	float					m_fActionTime = 0.0f;
	bool					m_bAction;
	float					m_fPatrolTime = 8.0f;

	D3DXVECTOR3				m_vFrom = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3				m_vTo = D3DXVECTOR3(0, 0, 0);

	BoundingSphere			m_sphere;

	cSkill*					m_pSkill = nullptr;
	float					m_fTargetRange=0.0f;
	bool					m_bSkillStart = false;

public:
	cAction(cGameObject* _pOwner);
	~cAction();

	cGameObject*			GetOwner();
	void					SetOwner(cGameObject* _pOwner);
	cGameObject*			GetTarget();
	void					SetTarget(cGameObject* _pTarget);
	void					Start();
	void					Stop();
	void					SetDelegate(cActionDelegate* _pDelegate);
	void					SetFrom(const D3DXVECTOR3& _from);
	void					SetTo(const D3DXVECTOR3& _to);
	void					SetActionTime(const float& _actiontime);

	void					ReadyMoveTo(const D3DXVECTOR3& _vTo);
	void					MoveTo();
	void					ReadyHeadTo(const D3DXVECTOR3& _vTo);
	void					HeadTo();
	void					ReadyPatrol(const D3DXVECTOR3& _vCenter);
	void					Patrol();
	void					ReadyAttack(cSkill* _pSkill);
	void					Attack();
	void					ReadyStun(const float& _stunTime);
	void					Stun();
	virtual	void			OnSkillDelegate(cSkill* _pSender);
};

