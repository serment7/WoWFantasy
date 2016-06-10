#pragma once
#include "cIState.h"

class cPlayerState :
	public cIState
{
private:
	cIState*				m_pState=nullptr;
	Packet_SkillKey* packet_skill = nullptr;
	Packet_Move* packet_move = nullptr;
	Packet_Target* packet_target = nullptr;
	ST_PACKET				m_packet;
	std::vector<cSkill*>	m_vecSkill;
	size_t					m_mapTag=0;
	cGameObject*			m_pTarget=nullptr;
	
	POINT					m_ptCursor;

public:
	cPlayerState(cIState* _state);
	~cPlayerState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

