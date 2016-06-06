#include "stdafx.h"
#include "cPlayer.h"
#include"cPlayerControlState.h"
#include"cGameObject.h"
//#include"cStatus.h"

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
	
	SetStateMachine(new cStateMachine(this));
	GetStateMachine()->SetGlobalState(new cPlayerControlState);
}

void cPlayer::Update()
{
	cGameObject::Update();
	float roty=GetRotationY();
	static TCHAR c[100];
	sprintf_s(c, "%f.2", roty);
	SetWindowText(g_hWnd, c);
}

void cPlayer::Render()
{
	cGameObject::Render();
}
