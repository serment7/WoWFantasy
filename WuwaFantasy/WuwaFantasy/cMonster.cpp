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
	GetSkinnedMesh()->SetFolderName(MODEL_PATH.c_str());
	GetSkinnedMesh()->Load("TheKingOfLich/lich.X");

}

void cMonster::Update()
{
	cGameObject::Update();
}

void cMonster::Render()
{
	cGameObject::Render();
}