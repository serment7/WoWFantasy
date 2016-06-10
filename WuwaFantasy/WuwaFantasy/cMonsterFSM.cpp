#include "stdafx.h"
#include "cMonsterFSM.h"
#include "cMonsterState.h"
#include "cIdleState.h"

cMonsterFSM::cMonsterFSM(cGameObject * _pOwner, cIState * _pState)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cMonsterState(_pState));
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	CurrentState()->EnterState(_pOwner);
}

cMonsterFSM::~cMonsterFSM()
{
}
