#include "stdafx.h"
#include "cSupply.h"


cSupply::cSupply()
{
}

cSupply::~cSupply()
{
}

void cSupply::Use(cGameObject * _pTarget)
{

	if ((--m_unCarriedNum)<=0)
		delete this;
}
