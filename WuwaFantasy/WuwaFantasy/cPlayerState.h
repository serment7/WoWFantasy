#pragma once
#include "cIState.h"

class cPlayerState :
	public cIState
{
private:
	cIState*				m_pState=nullptr;
	Packet_Skill*			packet_skill = nullptr;
	ST_PACKET				m_packet;
	std::vector<cSkill*>	m_vecSkill;

public:
	cPlayerState(cIState* _state);
	~cPlayerState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

