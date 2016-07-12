#pragma once
#include "cGameObject.h"
class cBattleMage :
	public cGameObject
{
public:
	cBattleMage();
	cBattleMage(const ST_STATUS& _status);
	virtual ~cBattleMage();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

