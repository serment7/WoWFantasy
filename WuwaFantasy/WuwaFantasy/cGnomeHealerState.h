#pragma once
#include "cModelState.h"
class cGnomeHealerState :
	public cModelState
{
private:
	Packet_SetSkill*			packet_setskill;
	bool						m_bAttack=false;
	bool						m_bLive=true;
public:
	cGnomeHealerState();
	~cGnomeHealerState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

