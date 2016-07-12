#pragma once
#include "cGameObject.h"
class cNamedMonster :
	public cGameObject
{
public:
	cNamedMonster(const std::string& _name, const D3DXVECTOR3& _pos, cIState* _pState);
	cNamedMonster(const std::string& _name, const D3DXVECTOR3& _pos, cIState* _pState, const ST_STATUS& _status);
	virtual ~cNamedMonster();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

