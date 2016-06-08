#pragma once
#include "cIState.h"
#include"cAction.h"

class cMoveState;
class cGameObject;

class cApproachState :
	public cIState, public cActionDelegate
{
private:
	Packet_Target*			packet_target=nullptr;
	cAction*				m_pAction = nullptr;
	cGameObject*			m_pTarget = nullptr;
public:
	cApproachState();
	~cApproachState();

	static cApproachState* GetInstance()
	{
		static cApproachState instance;
		return &instance;
	}

	virtual void EnterState(cGameObject* _player);
	virtual void ExitState(cGameObject* _player);
	virtual void Execute(cGameObject* _player);
	virtual bool OnMessage(cGameObject* _player, const ST_PACKET& _packet);
	virtual void OnActionDelegate(cAction* _pSender);
};

