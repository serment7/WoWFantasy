
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
	//�Ҹ��ڿ��� ����� �� �� �� �� �ֹǷ� nRefCount�� +1
	cObject::IncRefCount();
	cObject::Release();
}
