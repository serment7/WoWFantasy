#pragma once
#include "cStateMachine.h"
class cPlayerFSM :
	public cStateMachine
{
public:
	cPlayerFSM(cGameObject* _pOwner);
	virtual ~cPlayerFSM();
	virtual bool MessageHandle(const ST_PACKET& msg);
};
