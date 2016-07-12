#pragma once
#include "cGameObject.h"
class cCombatNPC :
	public cGameObject
{
public:
	cCombatNPC(const std::string& _name, const D3DXVECTOR3& _pos, const D3DXVECTOR3& _vDir, cIState* _pState);
	cCombatNPC(const std::string& _name, const D3DXVECTOR3& _pos, const D3DXVECTOR3& _vDir, cIState* _pState, const ST_STATUS& _status);
	virtual ~cCombatNPC();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

