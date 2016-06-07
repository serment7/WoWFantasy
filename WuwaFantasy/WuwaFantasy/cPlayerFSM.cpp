#include "stdafx.h"
#include "cPlayerFSM.h"
#include "cIdleState.h"
#include "cGameObject.h"
#include"cMoveState.h"
#include"cPlayerGlobalState.h"

cPlayerFSM::cPlayerFSM(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
	SetGlobalState(new cPlayerGlobalState);
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	_pOwner->GetSkinnedMesh()->SetAnimationIndex(3);
}

cPlayerFSM::~cPlayerFSM()
{
}