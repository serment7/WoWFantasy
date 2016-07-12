#pragma once
#include "cIState.h"
#include"cAction.h"

class cAction;
class cMoveState;
class cAttackState;
class cApproachState;

class cMoveState :
	public cIState, public cActionDelegate
{
private:
	Packet_Pos*				packet_move=nullptr;
	cAction*				pAction = nullptr;
	cMoveState*				m_pMoveState = nullptr;
	cAttackState*			m_pAttackState = nullptr;
	cApproachState*			m_pApproachState = nullptr;
public:
	cMoveState();
	~cMoveState();

	static cMoveState* GetInstance()
	{
		static cMoveState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cAction* _pSender);
};