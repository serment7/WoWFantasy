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

void cCondition::Update(const float & _delta, bool & _lifeTime)
{
}

void cCondition::Render()
{
}

void cCondition::PostRender()
{
}
