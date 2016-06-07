#include "stdafx.h"
#include "cStateMachine.h"
#include"cGameObject.h"

cStateMachine::~cStateMachine()
{
	SAFE_DELETE(m_pGlobalState);
}
