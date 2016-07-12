#include "stdafx.h"
#include "cBattleMage.h"
#include "cCombatNPCFSM.h"
#include "cDworfMageState.h"

cBattleMage::cBattleMage()
{
	this->AddRef();
}

cBattleMage::cBattleMage(const ST_STATUS & _status)
{
	this->AddRef();
	GetStatus().Setup(_status);
}


cBattleMage::~cBattleMage()
{
}

void cBattleMage::Setup()
{
	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));

	SetStateMachine(new cCombatNPCFSM(this, new cDworfMageState));
	GetStateMachine()->Setup();
}

void cBattleMage::Update()
{
	cGameObject::Update();
}

void cBattleMage::Render()
{
	cGameObject::Render();
}
