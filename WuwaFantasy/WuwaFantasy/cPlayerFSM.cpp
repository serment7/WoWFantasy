#include "stdafx.h"
#include "cPlayerFSM.h"
#include "cMoveState.h"

cPlayerFSM::cPlayerFSM(cGameObject * _pOwner)
	:cStateMachine(_pOwner)
{
	SetCurrentState(new cMoveState);
}

cPlayerFSM::~cPlayerFSM()
{
}