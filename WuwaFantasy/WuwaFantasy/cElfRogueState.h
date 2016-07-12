#pragma once
#include "cModelState.h"
class cElfLogState :
	public cModelState
{
private:
	bool						m_bLive = true;
	bool						m_bAttack = false;
	Packet_SetSkill*				packet_setskill = nullptr;
public:
	cElfLogState();
	virtual ~cElfLogState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

