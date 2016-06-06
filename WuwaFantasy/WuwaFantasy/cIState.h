#pragma once

struct ST_PACKET;
class cGameObject;

class cIState
{
public:
	cIState() {};
	~cIState() {};

	virtual void EnterState(cGameObject* _entity) = 0;
	virtual void ChangeState(cGameObject* _entity) = 0;
	virtual void ExitState(cGameObject* _entity) = 0;
	virtual void Execute(cGameObject* _entity) = 0;
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet) = 0;
};

