#pragma once
#include "cIState.h"

class cPlayer;
class cPlayerControlState :
	public cIState<cPlayer>
{
public:
	cPlayerControlState();
	virtual ~cPlayerControlState();

	virtual void EnterState(cPlayer* _entity);
	virtual void ChangeState(cPlayer* _entity);
	virtual void ExitState(cPlayer* _entity);
	virtual void Execute(cPlayer* _entity);
	virtual bool OnMessage(cPlayer* _entity, const ST_PACKET& _packet);
};

