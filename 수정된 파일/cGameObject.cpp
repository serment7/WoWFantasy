
#include "stdafx.h"
#include "cGameObject.h"

cGameObject::cGameObject()
{
	cObject::AddRef();
}

cGameObject::~cGameObject()
{
	cObject::Release();
}

void cGameObject::Setup()
{

}

void cGameObject::Update()
{

}

void cGameObject::Render()
{

}

void cGameObject::Release()
{
	//소멸자에서 릴리즈를 한 번 더 해 주므로 nRefCount를 +1
	cObject::IncRefCount();
	cObject::Release();
}
