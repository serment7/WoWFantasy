#pragma once
#include "cIState.h"

class cDworfMageState :
	public cIState
{
private:

public:
	cDworfMageState();
	virtual ~cDworfMageState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

