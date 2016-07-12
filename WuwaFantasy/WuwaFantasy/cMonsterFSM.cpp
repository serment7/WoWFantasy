#include "stdafx.h"
#include "cMonsterFSM.h"
#include "cMonsterState.h"
#include "cPatrolState.h"
#include "cGameObject.h"
#include "cAction.h"

cMonsterFSM::cMonsterFSM(cGameObject * _pOwner, cIState * _pState)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cMonsterState(_pState));

	SetCurrentState(cPatrolState::GetInstance());
	cAction* pAction = m_pOwner->GetAction();
	pAction->ReadyPatrol(m_pOwner->GetVPos());
	pAction->Start();
	pAction->SetOwner(m_pOwner);
	pAction->SetFrom(m_pOwner->GetVPos());
	pAction->SetTo(m_pOwner->GetVPos());
	pAction->SetDelegate(cPatrolState::GetInstance());
}

cMonsterFSM::~cMonsterFSM()
{
}

void cMonsterFSM::Setup()
{
	GlobalState()->EnterState(m_pOwner);
	CurrentState()->EnterState(m_pOwner);
}
