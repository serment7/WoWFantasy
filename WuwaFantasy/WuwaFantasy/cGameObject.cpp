
#include "stdafx.h"
#include "cGameObject.h"
#include "cCondition.h"

cGameObject::cGameObject()
{
	g_pObjectManager->AddObject(this);
}

cGameObject::~cGameObject()
{
	SAFE_DELETE(m_chrSkinnedMesh);
	SAFE_DELETE(m_objSkinnedMesh);
	g_pObjectManager->RemoveObject(this);
}

void cGameObject::Update()
{
	for (auto conditionIter = m_listCondition.begin(); conditionIter != m_listCondition.end();
		++conditionIter)
	{
		(*conditionIter)->Update();
	}
	if (m_chrSkinnedMesh)
		m_chrSkinnedMesh->Update();
	if (m_objSkinnedMesh)
		m_objSkinnedMesh->Update();

	cObject::Update();
}

void cGameObject::Render()
{
	if (m_chrSkinnedMesh)
		m_chrSkinnedMesh->Render(NULL);
	if (m_objSkinnedMesh)
		m_objSkinnedMesh->Render(NULL);
}

void cGameObject::SetID(const size_t & _id)
{
	m_unID = _id;
}

void cGameObject::SetTag(const size_t & _tag)
{
	m_unTag = _tag;
}

const size_t & cGameObject::GetID()
{
	return m_unID;
}

const size_t & cGameObject::GetTag()
{
	return m_unTag;
}

void cGameObject::AddCondition(cCondition * _pCondition)
{
	m_listCondition.push_back(_pCondition);
}

cStatus & cGameObject::GetStatus()
{
	return m_pStatus;
}

void cGameObject::OnMessage(const ST_PACKET & _packet)
{
	if (m_pStateMachine)
	{

	}
}
