#pragma once
#include "cIState.h"

class cGameObject;

class cMonsterState :
	public cIState
{
private:
	
	cIState*			m_pState = nullptr;
	cGameObject*			m_pTarget = nullptr;
	std::vector<size_t>	m_vecTargetTag;
	Packet_Target*		packet_target=nullptr;

	D3DXVECTOR3			m_vPos = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3			m_vTarget = D3DXVECTOR3(0, 0, 0);
	float				m_fRange = 0.0f;
	float				m_fRecognitionRange = MONSTER_RANGE*MONSTER_RANGE;
	bool				m_bAttack=false;
	
public:
	cMonsterState(cIState* _pState);
	~cMonsterState();

	virtual void	EnterState(cGameObject* _entity);
	virtual void	ExitState(cGameObject* _entity);
	virtual void	Execute(cGameObject* _entity);
	virtual bool	OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

