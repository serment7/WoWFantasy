#pragma once
#include "cGameObject.h"

class cIState;

class cMonster :
	public cGameObject
{
private:

public:
	cMonster(const std::string& _name, const D3DXVECTOR3& _pos,cIState* _pState);
	cMonster(const std::string& _name, const D3DXVECTOR3& _pos, cIState* _pState, const ST_STATUS& _status);
	virtual ~cMonster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

