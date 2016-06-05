#pragma once

struct ST_PACKET;

template <typename ENTITY_TYPE>
class cIState
{
public:
	cIState() {};
	virtual ~cIState() {};

	virtual void EnterState(ENTITY_TYPE*) = 0;
	virtual void ChangeState(ENTITY_TYPE*) = 0;
	virtual void ExitState(ENTITY_TYPE*) = 0;
	virtual void Execute(ENTITY_TYPE*) = 0;
	virtual bool OnMessage(ENTITY_TYPE*, const ST_PACKET&) = 0;
};

