#include "stdafx.h"
#include "cStateMachine.h"
#include"cGameObject.h"

cStateMachine::~cStateMachine()
{
	SAFE_DELETE(m_pGlobalState);
	SAFE_DELETE(m_pPreviousState);
	SAFE_DELETE(m_pCurrentState);
}
