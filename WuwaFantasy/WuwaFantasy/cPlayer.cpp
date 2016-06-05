#include "stdafx.h"
#include "cPlayer.h"
#include"cPlayerControlState.h"
#include"cGameObject.h"

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
	SetStateMachine(new cStateMachine(this));
	GetStateMachine()->SetGlobalState(new cPlayerControlState);
}

void cPlayer::Update()
{
	cGameObject::Update();
}

void cPlayer::Render()
{
	cGameObject::Render();
}
