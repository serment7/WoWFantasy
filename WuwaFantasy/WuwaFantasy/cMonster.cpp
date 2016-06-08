#include "stdafx.h"
#include "cMonster.h"
#include "cSkinnedMesh.h"

cMonster::cMonster()
{
	
}

cMonster::~cMonster()
{
}

void cMonster::Setup()
{
	GetChrSkinnedMesh()->SetFolderName(MODEL_PATH.c_str());
	GetChrSkinnedMesh()->Load("TheKingOfLich/lich.X");

}

void cMonster::Update()
{
	cGameObject::Update();
}

void cMonster::Render()
{
	cGameObject::Render();
}