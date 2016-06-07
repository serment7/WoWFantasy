#pragma once
#include "cIState.h"
#include "cAction.h"

class cIdleState :
	public cIState
{
private:
	Packet_Attack*			packet_attack = nullptr;
	Packet_Move*			packet_move = nullptr;
	cAction*				pAction = nullptr;
public:
	cIdleState();
	~cIdleState();

	static cIdleState* GetInstance()
	{
		static cIdleState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ChangeState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cAction* _pSender);
};

