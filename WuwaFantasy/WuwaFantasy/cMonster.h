#pragma once
#include "cMovingObject.h"

class cStateMachine;

class cMonster :
	public cMovingObject
{
private:


public:
	cMonster();
	virtual ~cMonster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();
};

