#pragma once
#include "cEntityState.h"

class cBossMonsterState :
	public cEntityState
{
private:
	std::vector<size_t>	m_vecTargetTag;
	Packet_Pos*		packet_move = nullptr;
	Packet_Hit*			packet_hit = nullptr;
	Packet_Target*		packet_target = nullptr;
	Packet_Attack*		packet_attack = nullptr;
	Packet_AddCondition*	packet_condition = nullptr;
	Packet_SetSkill*	packet_setskill = nullptr;
	ST_PACKET			m_packet;

	D3DXVECTOR3			m_vPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3			m_vTargetPos = D3DXVECTOR3(0, 0, 0);
	float				m_fTargetRange = 0.0f;
	float				m_fSearchTarget = 0.0f;
	size_t				m_searchIndex = 0;
	std::map<size_t, cGameObject*> m_mapTargetList;

	D3DXVECTOR3			m_vRespawnPos = D3DXVECTOR3(0, 0, 0);
	float				m_fRespawnPassedTime = 0.0f;
	float				m_fRespawnTime = 30.0f;
	float				m_fDeathMotionTime = 12.0f;
	float				m_fPassedSkillTime = 0.0f;
	float				m_fPerSkill = 5.0f;

public:
	cBossMonsterState(cIState* _pState);
	virtual ~cBossMonsterState();

	virtual void		EnterState(cGameObject* _entity);
	virtual void		ExitState(cGameObject* _entity);
	virtual void		Execute(cGameObject* _entity);
	virtual bool		OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

