#include "stdafx.h"
#include "cPlayer.h"
#include"cGameObject.h"
#include "cPlayerFSM.h"
#include "cDworfMageState.h"

cPlayer::cPlayer()
	:cGameObject()
{
	this->AddRef();
}

cPlayer::cPlayer(const ST_STATUS & _status)
{
	GetStatus().Setup(_status);
}


cPlayer::~cPlayer()
{

}


void cPlayer::Setup()
{
	m_chrSkinnedMesh = new cSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0,0,-1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	GetStatus().SetSpeed(5.0f);
	
	SetStateMachine(new cPlayerFSM(this, new cDworfMageState));
	m_sphere.fRadius = 3;
	m_sphere.vCenter = D3DXVECTOR3(0, 0, 0);
	//SetStateMachine(new cHydraFSM(this));
}

void cPlayer::Update()
{
	cGameObject::Update();
}

void cPlayer::Render()
{
	cGameObject::Render();
}
