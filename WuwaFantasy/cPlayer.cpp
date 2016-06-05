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
	m_chrSkinnedMesh->Load("hFemale", "hFemale.X");
}

void cPlayer::Update()
{
	m_chrSkinnedMesh->Update();
}

void cPlayer::Render()
{
	m_chrSkinnedMesh->Render(NULL);
}

void cPlayer::Release()
{
	SAFE_RELEASE(m_chrSkinnedMesh);
}
