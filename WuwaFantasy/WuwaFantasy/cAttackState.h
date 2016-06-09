#pragma once
#include "cIState.h"
#include "cAction.h"

class cMoveState;

class cAttackState :
	public cIState,public cActionDelegate
{
private:
	cMoveState*			m_pMoveState=nullptr;
	cAction*			m_pAction = nullptr;
	Packet_Attack*		packet_target=nullptr;
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

