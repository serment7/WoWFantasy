#include "stdafx.h"
#include "cObjectManager.h"
#include"cObject.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cObject * _object)
{
	m_mapObjectByID.insert(std::pair<size_t,cObject*>(_object->GetID(),_object));
	m_mapObjectByTag[_object->GetTag()].push_back(_object);
}

void cObjectManager::RemoveObject(cObject * _object)
{
	m_mapObjectByTag.erase(_object->GetTag());
	m_mapObjectByID.erase(_object->GetID());
}

cObject * cObjectManager::FindObjectByID(const size_t & _id)
{
	return m_mapObjectByID.find(_id)->second;
}

std::vector<cObject*>& cObjectManager::FindObjectByTag(const size_t & _tag)
{
	return m_mapObjectByTag.find(_tag)->second;
}



void cObjectManager::Destroy()
{
#ifdef _DEBUG
	assert(m_mapObjectByID.empty() && "소툈E프갋않은 객체가 있습니다");
#endif
}
