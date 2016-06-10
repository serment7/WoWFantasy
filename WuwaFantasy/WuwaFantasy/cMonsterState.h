#pragma once
#include "cIState.h"

class cGameObject;
class cStatus;

class cMonsterState :
	public cIState
{
private:

	cStatus*			m_pStatus=nullptr;

	cIState*			m_pState = nullptr;
	cGameObject*		m_pTarget = nullptr;
	std::vector<size_t>	m_vecTargetTag;
	Packet_Approach*		packet_target=nullptr;
	Packet_Move*		packet_move = nullptr;
	ST_PACKET			m_packet;
	
	D3DXVECTOR3			m_vPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3			m_vTargetPos = D3DXVECTOR3(0, 0, 0);
	float				m_fTargetRange = 0.0f;
	bool				m_bAttack=false;

	D3DXVECTOR3			m_vRespawnPos = D3DXVECTOR3(0, 0, 0);
	float				m_fRespawnPassedTime = 0.0f;
	float				m_fRespawnTime = 0.0f;
	bool				m_bLive = true;
	
public:
	cMonsterState(cIState* _pState);
	~cMonsterState();

	virtual void	EnterState(cGameObject* _entity);
	virtual void	ExitState(cGameObject* _entity);
	virtual void	Execute(cGameObject* _entity);
	virtual bool	OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

