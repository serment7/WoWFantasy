#include "stdafx.h"
#include "cCombatNPCFSM.h"
#include "cCombatNPCState.h"
#include "cIdleState.h"
#include "cAction.h"
#include "cGameObject.h"

cCombatNPCFSM::cCombatNPCFSM(cGameObject* _pOwner, cIState* _pState)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cCombatNPCState(_pState));
	SetCurrentState(cIdleState::GetInstance());
	m_pOwner->GetAction()->SetOwner(_pOwner);
}


cCombatNPCFSM::~cCombatNPCFSM()
{
}

void cCombatNPCFSM::Setup()
{
	GlobalState()->EnterState(m_pOwner);
	CurrentState()->EnterState(m_pOwner);
}
