#include "stdafx.h"
#include "cPlayerFSM.h"
#include "cIdleState.h"
#include "cGameObject.h"
#include"cMoveState.h"

cPlayerFSM::cPlayerFSM(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
	SetCurrentState(cIdleState::GetInstance());
	_pOwner->GetSkinnedMesh()->SetAnimationIndex(3);
}

cPlayerFSM::~cPlayerFSM()
{
}

bool cPlayerFSM::MessageHandle(const ST_PACKET & msg)
{
	if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
	{
		return true;
	}

	if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
	{
		return true;
	}

	return false;
}
