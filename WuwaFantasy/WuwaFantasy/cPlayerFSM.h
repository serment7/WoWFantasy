#pragma once
#include "cStateMachine.h"

class cGameObject;

class cPlayerFSM :
	public cStateMachine
{
public:
	cPlayerFSM(cGameObject* _pOwner,cIState* _pState);
	virtual ~cPlayerFSM();

	virtual void Setup();
};
