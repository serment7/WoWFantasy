
#include "stdafx.h"
#include "cGameObject.h"
#include "cSkinnedMesh.h"

cGameObject::cGameObject()
{
	cObject::AddRef();
	m_mesh = new cSkinnedMesh();
}

cGameObject::~cGameObject()
{
	SAFE_DELETE(m_mesh);
	
}

void cGameObject::Setup()
{

}

void cGameObject::Update()
{
	m_mesh->Update();
}

void cGameObject::Render()
{
	m_mesh->Render(NULL);
}

void cGameObject::Release()
{
	//소멸자에서 릴리즈를 한 번 더 해 주므로 nRefCount를 +1
	//cObject::IncRefCount();
	cObject::Release();
}

cStatus & cGameObject::GetStatus()
{
	return m_ChrStatus;
}
