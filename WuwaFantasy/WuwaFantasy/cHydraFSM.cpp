#include "stdafx.h"
#include "cHydraFSM.h"
#include "cGameObject.h"
#include "cHydraState.h"
#include "cIdleState.h"

cHydraFSM::cHydraFSM(cGameObject* _pOwner)
{
	m_pOwner = _pOwner;
	
	m_pOwner->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "Hydra");
	m_pOwner->GetChrSkinnedMesh()->Load("Hydra.X");
	//m_pOwner->GetSkinnedMesh()->SetFolderName(MODEL_PATH + "DworfBattleMage");
	//m_pOwner->GetSkinnedMesh()->Load("DworfBattleMage.X");
	SetGlobalState(new cHydraState);
	GlobalState()->EnterState(_pOwner);

	SetCurrentState(cIdleState::GetInstance());
	CurrentState()->EnterState(_pOwner);
}

cHydraFSM::~cHydraFSM()
{
}
