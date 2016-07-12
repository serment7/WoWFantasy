#pragma once
#include "cEntityState.h"

const float REACTION_DISTANCE = 3.0f;
const float KEEP_MIN_DISTANCE = 1.5f;
const float KEEP_MAX_DISTANCE = 10.0f;

class cUITextView;

class cCombatNPCState :
	public cEntityState
{
private:
	cGameObject*		m_pLeader = nullptr;
	cGameObject*		m_pParty = nullptr;
	size_t				m_leaderID = MAXSIZE_T;
	D3DXVECTOR3			m_vLeaderPos;
	D3DXVECTOR3			m_vLeaderDir;

	D3DXVECTOR3			m_vCurPos;
	D3DXVECTOR3			m_vVelocity;
	int					m_nVelocityNum=0;

	ST_PACKET			m_packet;
	Packet_Party*		packet_party=nullptr;
	Packet_Target*		packet_target = nullptr;
	Packet_Pos*			packet_move=nullptr;
	Packet_SetSkill*	packet_setskill = nullptr;
	Packet_Hit*			packet_hit = nullptr;
	Packet_Attack*		packet_attack = nullptr;
	Packet_AddCondition* packet_condition = nullptr;

	std::vector<cGameObject*> m_vecParty;
	std::map<size_t,cGameObject*> m_mapNeedHelp;
	BoundingSphere		m_boundsphere;

	int						m_nWeightNum = -1;
	char					m_chWeightKey = -1;
	float					m_fSkillPeriod = 0.0f;
	bool					m_bCanAttack=false;
	float					m_fPassedSkillTime = 0.0f;
	float					m_fPerSkill=5.0f;
	bool					m_bCoolDown = false;
	bool					m_bAttack = false;

public:
	cCombatNPCState(cIState* _pState);
	virtual ~cCombatNPCState();

	virtual void EnterState(cGameObject* _entity);
	virtual void ExitState(cGameObject* _entity);
	virtual void Execute(cGameObject* _entity);
	virtual bool OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

