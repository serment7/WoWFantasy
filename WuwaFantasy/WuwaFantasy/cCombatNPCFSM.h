#pragma once
#include "cStateMachine.h"
class cCombatNPCFSM :
	public cStateMachine
{
public:
	cCombatNPCFSM(cGameObject* _pOwner, cIState* _pState);
	virtual ~cCombatNPCFSM();

	virtual void Setup();
};

