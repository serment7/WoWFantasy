#pragma once
#include "cIState.h"
#include"cIAction.h"

class cGameObject;
class cActionMove;

class cMoveState :
	public cIState,public cDelegate
{
private:
	Packet_Attack*			packet_attack = nullptr;
	Packet_Move*			packet_move = nullptr;
public:
	cMoveState();
	virtual ~cMoveState();

	virtual void EnterState(cGameObject* _player);
	virtual void ChangeState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cIAction* _pSender);
};