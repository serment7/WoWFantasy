// cGameObject.cpp: implementation of the cGameObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cGameObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cGameObject::cGameObject()
{
	cObject::AddRef();
}

cGameObject::~cGameObject()
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
	cObject::Release();
}
