#include "stdafx.h"
#include "cObjectManager.h"
#include"cGameObject.h"

cObjectManager::cObjectManager()
{
}


cObjectManager::~cObjectManager()
{
}

void cObjectManager::AddObject(cGameObject * _object)
{
	m_mapObjectByID.insert(std::pair<size_t,cGameObject*>(m_unInstanceID,_object));
	_object->SetID(m_unInstanceID++);
	m_mapObjectByTag[_object->GetTag()].push_back(_object);
}

void cObjectManager::RemoveObject(cGameObject * _object)
{
	m_mapObjectByTag.erase(_object->GetTag());
	m_mapObjectByID.erase(_object->GetID());
}

cGameObject * cObjectManager::FindObjectByID(const size_t & _id)
{
	return m_mapObjectByID.find(_id)->second;
}

std::vector<cGameObject*>& cObjectManager::FindObjectByTag(const size_t & _tag)
{
	return m_mapObjectByTag.find(_tag)->second;
}



void cObjectManager::Destroy()
{
#ifdef _DEBUG
	assert(m_mapObjectByID.empty() && "소툈E프갋않은 객체가 있습니다");
#endif
}
