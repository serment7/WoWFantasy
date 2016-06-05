#pragma once
#include "cIState.h"

class cPlayer;
class cPlayerControlState :
	public cIState<cPlayer>
{
public:
	cPlayerControlState();
	virtual ~cPlayerControlState();

	virtual void EnterState(cPlayer* _player);
	virtual void ChangeState(cPlayer* _player);
	virtual void ExitState(cPlayer* _player);
	virtual void Execute(cPlayer* _player);
	virtual bool OnMessage(cPlayer* _player, const ST_PACKET& _packet);
};

