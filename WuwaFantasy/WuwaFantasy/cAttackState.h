#pragma once
#include "cIState.h"

class cAction;

class cAttackState :
	public cIState
{
private:
	Packet_Attack*			packet_attack = nullptr;
	cAction*				pAction = nullptr;
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
};

