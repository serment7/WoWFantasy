#include "stdafx.h"
#include "cIAction.h"
#include "cGameObject.h"

cIAction::cIAction()
{
}


cIAction::~cIAction()
{
	SAFE_RELEASE(m_pOwner);
}

void cIAction::SetOwner(cGameObject * _pOwner)
{
	SAFE_RELEASE(m_pOwner);
#ifdef _DEBUG
	assert(_pOwner && "SetOwner() received null ptr");
#endif
	m_pOwner->AddRef();
	m_pOwner = _pOwner;
}

void cIAction::SetActionTime(const float & _fActionTime)
{
	m_fActionTime = _fActionTime;
}
