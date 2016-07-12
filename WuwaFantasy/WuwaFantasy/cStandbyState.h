#pragma once
#include "cIState.h"
class cStandbyState :
	public cIState
{
public:
	cStandbyState();
	~cStandbyState();

	static cStandbyState* GetInstance()
	{
		static cStandbyState instance;
		return &instance;
	}

	virtual void		EnterState(cGameObject* _entity);
	virtual void		ExitState(cGameObject* _entity);
	virtual void		Execute(cGameObject* _entity);
	virtual bool		OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
};

