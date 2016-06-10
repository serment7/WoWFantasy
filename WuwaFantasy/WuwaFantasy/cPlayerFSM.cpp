#include "stdafx.h"
#include "cPlayerFSM.h"
#include "cPlayerState.h"
#include "cIdleState.h"
#include "cDworfMageState.h"

cPlayerFSM::cPlayerFSM(cGameObject* _pOwner , cIState* _pState)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cPlayerState(_pState));
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	CurrentState()->EnterState(_pOwner);
}


cPlayerFSM::~cPlayerFSM()
{
}
