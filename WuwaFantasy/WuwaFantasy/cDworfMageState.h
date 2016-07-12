#pragma once
#include "cModelState.h"

class cDworfMageState :
	public cModelState
{
private:
	bool						m_bLive = true;
	bool						m_bAttack = false;
	Packet_SetSkill*				packet_setskill = nullptr;
public:
	cDworfMageState();
	virtual ~cDworfMageState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

