#pragma once

struct ST_PACKET;
class cGameObject;

class cIdleState;
class cMoveState;
class cAttackState;
class cApproachState;
class cStandbyState;
class cPatrolState;
class cStunState;

class cIState
{
private:
	cIdleState*				m_pIdleState = nullptr;
	cMoveState*				m_pMoveState = nullptr;
	cAttackState*			m_pAttackState = nullptr;
	cApproachState*			m_pApproachState = nullptr;
	cStandbyState*			m_pStatdbyState = nullptr;
	cPatrolState*			m_pPatrolState = nullptr;
	cStunState*				m_pStunState = nullptr;
public:
	cIState();
	virtual ~cIState() {};

	virtual void		EnterState(cGameObject* _entity) = 0;
	virtual void		ExitState(cGameObject* _entity) = 0;
	virtual void		Execute(cGameObject* _entity) = 0;
	virtual bool		OnMessage(cGameObject* _entity, const ST_PACKET& _packet) = 0;
	bool				MessageCatch(cGameObject* _entity,const ST_PACKET& _packet);
};