#include "stdafx.h"
#include "cCombatNPC.h"
#include "cCombatNPCFSM.h"

cCombatNPC::cCombatNPC(const std::string & _name, const D3DXVECTOR3 & _pos, const D3DXVECTOR3& _vDir, cIState * _pState)
{
	this->AddRef();
	SetName(_name);
	m_chrSkinnedMesh = new cSkinnedMesh;
	m_objSkinnedMesh = new cWeaponSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	SetVPos(_pos);
	SetVDir(_vDir);

	SetTag(g_pGameManager->FindObjectType("combatnpc"));
	g_pObjectManager->AddObject(this);

	SetStateMachine(new cCombatNPCFSM(this, _pState));
}

cCombatNPC::cCombatNPC(const std::string & _name, const D3DXVECTOR3 & _pos, const D3DXVECTOR3& _vDir, cIState * _pState, const ST_STATUS & _status)
	:cCombatNPC::cCombatNPC(_name, _pos, _vDir,_pState)
{
	GetStatus().Setup(_status);
}

cCombatNPC::~cCombatNPC()
{
}

void cCombatNPC::Setup()
{
	GetStateMachine()->Setup();
}

void cCombatNPC::Update()
{
	cGameObject::Update();
}

void cCombatNPC::Render()
{
	cGameObject::Render();
}
