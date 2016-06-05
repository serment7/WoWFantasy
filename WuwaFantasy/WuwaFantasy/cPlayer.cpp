#include "stdafx.h"
#include "cPlayer.h"


cPlayer::cPlayer()
{
	this->AddRef();
}


cPlayer::~cPlayer()
{

}


void cPlayer::Setup()
{
	m_chrSkinnedMesh = new cSkinnedMesh;
	
	//m_chrSkinnedMesh->Load(MODEL_PATH, "hFemale/hFemale.X");
	m_chrSkinnedMesh->Load("./hFemale/" , "hFemale.X");
}

void cPlayer::Update()
{
	cGameObject::Update();
}

void cPlayer::Render()
{
	cGameObject::Render();
}
