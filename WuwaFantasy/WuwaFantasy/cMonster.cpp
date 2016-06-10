#include "stdafx.h"
#include "cMonster.h"
#include "cSkinnedMesh.h"
#include "cMonsterFSM.h"

cMonster::cMonster(const std::string& _name, cIState* _pState)
{
	this->AddRef();

	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));

	SetTag(g_pGameManager->FindObjectType("monster"));
	g_pObjectManager->AddObject(this);

	SetStateMachine(new cMonsterFSM(this, _pState));
}

cMonster::~cMonster()
{
	
}

void cMonster::Setup()
{

}

void cMonster::Update()
{
	cGameObject::Update();
}

void cMonster::Render()
{
	cGameObject::Render();
}