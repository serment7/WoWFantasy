#include "stdafx.h"
#include "cHydraFSM.h"
#include "cGameObject.h"
#include "cHydraState.h"
#include "cIdleState.h"

cHydraFSM::cHydraFSM(cGameObject* _pOwner)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cHydraState);
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	CurrentState()->EnterState(_pOwner);
}

cHydraFSM::~cHydraFSM()
{
}
