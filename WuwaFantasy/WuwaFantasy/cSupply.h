#pragma once
#include "cItem.h"
class cSupply :
	public cItem
{
private:
	float			m_fPassedTime=0.0f;
	float			m_fEffectTime=0.0f;
	size_t			m_unCarriedNum = 0;
	std::vector<std::string> effect;

public:
	cSupply();
	cSupply(size_t _unCarriedNum)
		:m_unCarriedNum(_unCarriedNum) {}
	virtual ~cSupply();
	virtual void Use(cGameObject* _pTarget);
};

