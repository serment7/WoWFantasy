#pragma once
#include "cMovingObject.h"

class cMonster :
	public cMovingObject
{
private:
	std::string			m_resource;
	std::string			m_name;

public:
	cMonster();
	virtual ~cMonster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

