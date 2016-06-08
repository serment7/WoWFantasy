#include "stdafx.h"
#include "cPlayer.h"
#include"cGameObject.h"
#include"cDworfMageFSM.h"
#include "cHydraFSM.h"

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
	
	SetStateMachine(new cDworfMageFSM(this));
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
