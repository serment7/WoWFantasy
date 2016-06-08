#pragma once
#include "cIState.h"

class cAction;
class cMoveState;

class cAttackState :
	public cIState
{
private:
	cMoveState*			m_pMoveState=nullptr;
public:
	cAttackState();
	~cAttackState();

	static cAttackState* GetInstance()
	{
		static cAttackState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cAction* _pSender);
};

