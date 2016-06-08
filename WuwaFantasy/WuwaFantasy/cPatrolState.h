#pragma once
#include "cIState.h"

class cMoveState;

class cPatrolState :
	public cIState
{
private:
	cMoveState*			m_pMoveState;
public:
	cPatrolState();
	~cPatrolState();

	static cPatrolState* GetInstance()
	{
		static cPatrolState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
};

