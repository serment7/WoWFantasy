#pragma once
#include "cIState.h"
class cStunState :
	public cIState
{
private:
	ST_PACKET				m_packet;
public:
	cStunState();
	~cStunState();

	static cStunState* GetInstance()
	{
		static cStunState instance;
		return &instance;
	}

	virtual void		EnterState(cGameObject* _entity);
	virtual void		ExitState(cGameObject* _entity);
	virtual void		Execute(cGameObject* _entity);
	virtual bool		OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

