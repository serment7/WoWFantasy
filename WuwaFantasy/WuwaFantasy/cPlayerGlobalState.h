#pragma once
#include "cIState.h"
class cPlayerGlobalState :
	public cIState
{
public:
	cPlayerGlobalState();
	virtual ~cPlayerGlobalState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ChangeState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

