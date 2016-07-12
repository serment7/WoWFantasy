#include "stdafx.h"
#include "cStateMachine.h"
#include"cGameObject.h"

cStateMachine::~cStateMachine()
{
	SAFE_DELETE(m_pGlobalState);
}

bool cStateMachine::MessageHandle(const ST_PACKET & msg)
{
	if (m_pOwner->GetID() != msg.receiver)
		return false;

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

void cStateMachine::ChangeState(cIState * _pNewState)
{

#ifdef _DEBUG
	assert(_pNewState && "ChangeState() received null ptr");
#endif
	m_pPreviousState = m_pCurrentState;
	m_pCurrentState->ExitState(m_pOwner);

	m_pCurrentState = _pNewState;
	m_pCurrentState->EnterState(m_pOwner);

}

void cStateMachine::RevertState()
{
	ChangeState(m_pPreviousState);
}
