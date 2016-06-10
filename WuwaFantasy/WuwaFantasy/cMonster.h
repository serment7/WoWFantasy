#pragma once
#include "cMovingObject.h"

class cIState;

class cMonster :
	public cMovingObject
{
private:

public:
	cMonster(const std::string& _name,cIState* _pState);
	virtual ~cMonster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

