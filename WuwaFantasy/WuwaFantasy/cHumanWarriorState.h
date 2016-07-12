#pragma once
#include "cModelState.h"
class cHumanWarriorState :
	public cModelState
{
private:
	Packet_SetSkill*				packet_setskill = nullptr;
	bool							m_bLive=true;
	bool							m_bAttack=false;
public:
	cHumanWarriorState();
	virtual ~cHumanWarriorState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

