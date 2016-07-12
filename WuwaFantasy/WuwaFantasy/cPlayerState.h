#pragma once
#include "cEntityState.h"

class cCondition;
class cStatus;
class cUIObject;
class cUITextView;

class cPlayerState :
	public cEntityState
{
private:
	D3DXVECTOR3				m_vCurPos;

	Packet_Pos*				packet_move = nullptr;
	Packet_Target*			packet_target = nullptr;
	Packet_Hit*				packet_hit=nullptr;
	Packet_Attack*			packet_attack = nullptr;
	Packet_SetSkill*		packet_setskill = nullptr;
	Packet_Party*			packet_party = nullptr;
	Packet_AddCondition*	packet_condition=nullptr;
	Packet_UseSkill*		packet_useskill = nullptr;
	ST_PACKET				m_packet;
	
	Packet_Zoom*			packet_zoom;

	std::vector<size_t>		m_vecTargetTag;
	std::vector<cGameObject*> m_vecPartyNPC;

	size_t					m_mapTag=0;
	
	POINT					m_ptCursor;

public:
	cPlayerState(cIState* _state);
	virtual ~cPlayerState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

