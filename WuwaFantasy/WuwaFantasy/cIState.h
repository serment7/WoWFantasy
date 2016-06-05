#pragma once

struct ST_PACKET;

template <typename ENTITY_TYPE>
class cIState
{
public:
	cIState() {};
	virtual ~cIState() {};

	virtual void EnterState(ENTITY_TYPE* _entity) = 0;
	virtual void ChangeState(ENTITY_TYPE* _entity) = 0;
	virtual void ExitState(ENTITY_TYPE* _entity) = 0;
	virtual void Execute(ENTITY_TYPE* _entity) = 0;
	virtual bool OnMessage(ENTITY_TYPE* _entity, const ST_PACKET& _packet) = 0;
};

