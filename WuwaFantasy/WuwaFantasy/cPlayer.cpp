#include "stdafx.h"
#include "cPlayer.h"
#include"cGameObject.h"
#include "cPlayerFSM.h"

cPlayer::cPlayer(const std::string & _name, const D3DXVECTOR3 & _pos, const D3DXVECTOR3 & _vDir, cIState * _pState)
{
	this->AddRef();
	SetName(_name);
	m_chrSkinnedMesh = new cSkinnedMesh;
	m_objSkinnedMesh = new cWeaponSkinnedMesh;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));
	SetVPos(_pos);
	SetVDir(_vDir);

	SetTag(g_pGameManager->FindObjectType("player"));
	g_pObjectManager->AddObject(this);

	SetStateMachine(new cPlayerFSM(this, _pState));
}

cPlayer::cPlayer(const std::string & _name, const D3DXVECTOR3 & _pos, const D3DXVECTOR3 & _vDir, cIState * _pState, const ST_STATUS & _status)
	:cPlayer::cPlayer(_name, _pos,_vDir, _pState)
{
	GetStatus().Setup(_status);
}

cPlayer::~cPlayer()
{

}

void cPlayer::Setup()
{
	GetStateMachine()->Setup();
}

void cPlayer::Update()
{
	cGameObject::Update();
}

void cPlayer::Render()
{
	cGameObject::Render();
}
