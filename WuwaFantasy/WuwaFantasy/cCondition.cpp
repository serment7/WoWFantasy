#include "stdafx.h"
#include "cCondition.h"


cCondition::cCondition()
{
}


cCondition::~cCondition()
{
}

void cCondition::SetOwner(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
}

cGameObject * cCondition::GetOwner() const
{
	return m_pOwner;
}
