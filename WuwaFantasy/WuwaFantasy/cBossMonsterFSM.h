#pragma once
#include "cStateMachine.h"
class cBossMonsterFSM :
	public cStateMachine
{
public:
	cBossMonsterFSM(cGameObject* _pOwner, cIState* _pState);
	virtual ~cBossMonsterFSM();

	virtual void Setup();
};

