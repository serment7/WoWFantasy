#include "stdafx.h"
#include "cBossMonsterState.h"
#include "cBossMonsterFSM.h"
#include "cPatrolState.h"
#include "cGameObject.h"
#include "cAction.h"

cBossMonsterFSM::cBossMonsterFSM(cGameObject* _pOwner, cIState* _pState)
{
	m_pOwner = _pOwner;
	m_pOwner->GetAction()->SetOwner(_pOwner);

	SetGlobalState(new cBossMonsterState(_pState));

	SetCurrentState(cPatrolState::GetInstance());
	cAction* pAction = m_pOwner->GetAction();
	pAction->ReadyPatrol(m_pOwner->GetVPos());
	pAction->Start();
	pAction->SetOwner(m_pOwner);
	pAction->SetFrom(m_pOwner->GetVPos());
	pAction->SetTo(m_pOwner->GetVPos());
	pAction->SetDelegate(cPatrolState::GetInstance());
}


cBossMonsterFSM::~cBossMonsterFSM()
{
}

void cBossMonsterFSM::Setup()
{
	GlobalState()->EnterState(m_pOwner);
	CurrentState()->EnterState(m_pOwner);
}
