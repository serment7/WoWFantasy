#include "stdafx.h"
#include "cObjectManager.h"
#include"cObject.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::RegisterObject(cObject * _object)
{
	size_t d = 3;
	m_mapObjectByID.insert(std::pair<size_t,cObject*>(d,_object));
	m_mapObjectByTag.insert(std::pair<size_t, cObject*>(d, _object));
}

void cObjectManager::UnregisterObject(cObject * _object)
{
}

cObject * cObjectManager::FindObjectByID(const size_t _id)
{
	return m_mapObjectByID.find(_id)->second;
}

cObject * cObjectManager::FindObjectByTag(const size_t _tag)
{
	return m_mapObjectByTag.find(_tag)->second;
}

void cObjectManager::Destroy()
{
#ifdef _DEBUG
	assert(m_mapObjectByID.empty() && "소멸되지 않은 객체가 있습니다");
#endif
}
