#pragma once
#include "cIState.h"
#include"cAction.h"

class cGameObject;
class cActionMove;

class cMoveState :
	public cIState
{
private:
	Packet_Move* packet_move;
	cAction*				pAction = nullptr;
public:
	cMoveState();
	virtual ~cMoveState();

	static cMoveState* GetInstance()
	{
		static cMoveState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ChangeState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cAction* _pSender);
};