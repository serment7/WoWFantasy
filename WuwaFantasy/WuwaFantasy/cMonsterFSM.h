#pragma once
#include "cStateMachine.h"

class cGameObject;

class cMonsterFSM :
	public cStateMachine
{
public:
	cMonsterFSM(cGameObject* _pOwner, cIState* _pState);
	virtual ~cMonsterFSM();
	virtual void Setup();
};

