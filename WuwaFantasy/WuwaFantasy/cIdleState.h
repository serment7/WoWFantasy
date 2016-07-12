#pragma once
#include "cIState.h"

class cMoveState;
class cAttackState;
class cApproachState;

class cIdleState :
	public cIState
{
public:
	cIdleState();
	~cIdleState();

	static cIdleState* GetInstance()
	{
		static cIdleState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
};
