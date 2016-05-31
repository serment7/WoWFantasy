#include "stdafx.h"
#include "cObjectManager.h"
#include"cObject.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(iObject * _object)
{
	m_setObject.insert(_object);
}

void cObjectManager::RemoveObject(iObject * _object)
{
	m_setObject.erase(_object);
}

void cObjectManager::Destroy()
{
#ifdef _DEBUG
	assert(m_setObject.empty() && "소멸되지 않은 객체가 있습니다");
#endif
}
