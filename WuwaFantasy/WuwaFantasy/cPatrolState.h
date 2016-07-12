#pragma once
#include "cIState.h"
#include "cAction.h"
class cPatrolState :
	public cIState,public cActionDelegate
{
private:
	Packet_Pos*		packet_pos=nullptr;
	cAction*		m_pAction = nullptr;
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
	virtual void OnActionDelegate(cAction* _pSender);
};

