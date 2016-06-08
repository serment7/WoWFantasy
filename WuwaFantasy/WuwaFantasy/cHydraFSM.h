#pragma once
#include "cStateMachine.h"

class cGameObject;

class cHydraFSM :
	public cStateMachine
{
public:
	cHydraFSM(cGameObject* _pOwner);
	virtual ~cHydraFSM();
};

