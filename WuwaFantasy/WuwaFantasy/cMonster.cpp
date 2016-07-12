#include "stdafx.h"
#include "cMonster.h"
#include "cSkinnedMesh.h"
#include "cMonsterFSM.h"

cMonster::cMonster(const std::string& _name,const D3DXVECTOR3& _pos,cIState* _pState)
{
	this->AddRef();
	SetName(_name);
	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	SetVPos(_pos);

	SetTag(g_pGameManager->FindObjectType("monster"));
	g_pObjectManager->AddObject(this);

	SetStateMachine(new cMonsterFSM(this, _pState));
}

cMonster::cMonster(const std::string & _name, const D3DXVECTOR3 & _pos, cIState * _pState, const ST_STATUS & _status)
:cMonster(_name, _pos, _pState)
{
	GetStatus().Setup(_status);
}

cMonster::~cMonster()
{
	
}

void cMonster::Setup()
{
	GetStateMachine()->Setup();
}

void cMonster::Update()
{
	cGameObject::Update();
}

void cMonster::Render()
{
	cGameObject::Render();
}