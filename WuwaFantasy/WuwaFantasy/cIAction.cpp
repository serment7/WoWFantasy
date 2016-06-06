#include "stdafx.h"
#include "cIAction.h"
#include "cGameObject.h"

cIAction::cIAction()
{
}


cIAction::~cIAction()
{
}

void cIAction::SetOwner(cGameObject * _pOwner)
{
#ifdef _DEBUG
	assert(_pOwner && "SetOwner() received null ptr");
#endif
	m_pOwner = _pOwner;
}

cGameObject * cIAction::GetOwner()
{
	return m_pOwner;
}

void cIAction::SetPassedTime(const float & _fPassedTime)
{
	m_fPassedTime = _fPassedTime;
}

void cIAction::SetActionTime(const float & _fActionTime)
{
	m_fActionTime = _fActionTime;
}

const float & cIAction::GetActionTime() const
{
	return m_fActionTime;
}

void cIAction::SetAction(bool _bAction)
{
	m_bAction = _bAction;
}

const float & cIAction::GetPassedTime() const
{
	return m_fPassedTime;
}

void cIAction::SetDelegate(cDelegate * _pDelegate)
{
	m_pDelegate = _pDelegate;
}

cDelegate* cIAction::GetDelegate()
{
	return m_pDelegate;
}

bool cIAction::IsAction()
{
	return m_bAction;
}
