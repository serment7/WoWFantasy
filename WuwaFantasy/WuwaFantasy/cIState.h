#pragma once

class cGameObject;

#define ENTITY_TYPE cGameObject

class cIState
{
public:
	cIState();
	virtual ~cIState();

	virtual void EnterState(ENTITY_TYPE*) = 0;
	virtual void ChangeState(ENTITY_TYPE*) = 0;
	virtual void ExitState(ENTITY_TYPE*) = 0;
};

