#include "stdafx.h"
#include "cPlayerFSM.h"
#include "cPlayerState.h"
#include "cIdleState.h"
#include "cDworfMageState.h"
#include "cGameObject.h"
#include "cAction.h"

cPlayerFSM::cPlayerFSM(cGameObject* _pOwner, cIState* _pState)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cPlayerState(_pState));
	SetCurrentState(cIdleState::GetInstance());
	m_pOwner->GetAction()->SetOwner(_pOwner);
}


cPlayerFSM::~cPlayerFSM()
{
}

void cPlayerFSM::Setup()
{
	GlobalState()->EnterState(m_pOwner);
	CurrentState()->EnterState(m_pOwner);
}
