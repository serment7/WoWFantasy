#include "stdafx.h"
#include "cPlayer.h"
#include"cGameObject.h"
#include"cPlayerFSM.h"

cPlayer::cPlayer()
{
	this->AddRef();
	folder = MODEL_PATH + "/hFemale";
	filename = "hFemale.X";
}


cPlayer::~cPlayer()
{

}


void cPlayer::Setup()
{
	m_chrSkinnedMesh = new cSkinnedMesh;
	m_chrSkinnedMesh->SetFolderName(folder);
	m_chrSkinnedMesh->Load(filename.c_str());
	m_chrSkinnedMesh->SetAnimationIndex(4);
	SetVDir(D3DXVECTOR3(0,0,-1));
	GetStatus().SetSpeed(5.0f);
	
	SetStateMachine(new cPlayerFSM(this));
}

void cPlayer::Update()
{
	cGameObject::Update();
}

void cPlayer::Render()
{
	cGameObject::Render();
}
