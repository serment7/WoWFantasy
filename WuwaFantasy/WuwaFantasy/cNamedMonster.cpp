#include "stdafx.h"
#include "cNamedMonster.h"
#include "cBossMonsterFSM.h"

cNamedMonster::cNamedMonster(const std::string& _name, const D3DXVECTOR3& _pos, cIState* _pState)
{
	this->AddRef();
	SetName(_name);
	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	SetVPos(_pos);

	SetTag(g_pGameManager->FindObjectType("monster"));
	g_pObjectManager->AddObject(this);

	SetStateMachine(new cBossMonsterFSM(this, _pState));
}

cNamedMonster::cNamedMonster(const std::string & _name, const D3DXVECTOR3 & _pos, cIState * _pState, const ST_STATUS & _status)
	:cNamedMonster::cNamedMonster(_name, _pos, _pState)
{	
	GetStatus().Setup(_status);
}


cNamedMonster::~cNamedMonster()
{
}

void cNamedMonster::Setup()
{
	GetStateMachine()->Setup();
}

void cNamedMonster::Update()
{
	cGameObject::Update();
}

void cNamedMonster::Render()
{
	cGameObject::Render();
}
