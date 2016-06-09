#pragma once
#include "cStateMachine.h"
class cDworfMageFSM :
	public cStateMachine
{
public:
	cDworfMageFSM(cGameObject* _pOwner);
	~cDworfMageFSM();
};
