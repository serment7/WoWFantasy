#include "stdafx.h"
#include "cHydra.h"
#include "cHydraState.h"
#include "cMonsterFSM.h"

cHydra::cHydra()
{
	this->AddRef();
	folder = MODEL_PATH + "Hydra";
	filename = "Hydra.X";
}

cHydra::cHydra(const ST_STATUS & _status)
{
	GetStatus().Setup(_status);
}

cHydra::~cHydra()
{
}

void cHydra::Setup()
{
	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	
	SetStateMachine(new cMonsterFSM(this,new cHydraState));
}

void cHydra::Update()
{
	cGameObject::Update();
}

void cHydra::Render()
{
	cGameObject::Render();
}
