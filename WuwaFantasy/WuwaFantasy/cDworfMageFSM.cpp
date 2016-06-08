#include "stdafx.h"
#include "cDworfMageFSM.h"
#include "cIdleState.h"
#include "cGameObject.h"
#include"cMoveState.h"
#include"cDworfMageState.h"

cDworfMageFSM::cDworfMageFSM(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "DworfBattleMage");
	m_pOwner->GetChrSkinnedMesh()->Load("DworfBattleMage.X");
	SetGlobalState(new cDworfMageState);
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	CurrentState()->EnterState(_pOwner);
}

cDworfMageFSM::~cDworfMageFSM()
{
}