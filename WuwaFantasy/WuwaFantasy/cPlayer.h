#pragma once
#include "cGameObject.h"

class cDworfMageFSM;
struct ST_STATUS;

class cPlayer : 
	public cGameObject
{
private:

public:
	cPlayer(const std::string& _name, const D3DXVECTOR3& _pos, const D3DXVECTOR3 & _vDir, cIState* _pState);
	cPlayer(const std::string& _name, const D3DXVECTOR3& _pos, const D3DXVECTOR3 & _vDir, cIState* _pState, const ST_STATUS& _status);
	virtual ~cPlayer();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

