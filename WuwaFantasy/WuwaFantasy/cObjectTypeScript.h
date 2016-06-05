#pragma once
#include "cIScript.h"

class cObjectTypeScript :
	public cIScript
{
private:
	cParsing*		m_pParser = nullptr;
	std::string			m_pToken;
	
	size_t			m_unObjectTypeIndex = 0;

public:
	cObjectTypeScript();
	virtual ~cObjectTypeScript();

	virtual void Update();
};

