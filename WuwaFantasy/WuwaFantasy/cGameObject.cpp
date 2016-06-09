#include "stdafx.h"
#include "cGameObject.h"
#include "cCondition.h"
#include "cAction.h"

cGameObject::cGameObject()
	:m_pAction(new cAction(this))
{
	ST_STATUS status;
	ZeroMemory(&status, sizeof(status));
	status.fSpeed = 1.0f;
	status.nMaxHP = 20;
	status.nCurrentHP = 20;
	m_pStatus.Setup(status);
	ZeroMemory(&m_sphere, sizeof(m_sphere));
	ZeroMemory(&m_box, sizeof(m_box));
}

cGameObject::~cGameObject()
{
	SAFE_DELETE(m_chrSkinnedMesh);
	SAFE_DELETE(m_objSkinnedMesh);
	SAFE_DELETE(m_pStateMachine);
	g_pObjectManager->RemoveObject(this);
}

void cGameObject::Update()
{
	cObject::Update();
	static bool bDeleteCondition=false;

	auto conditionIter = m_listCondition.begin();
	while (conditionIter != m_listCondition.end())
	{
		(*conditionIter)->Update(bDeleteCondition);
		if (!bDeleteCondition)
			m_listCondition.erase(conditionIter);
		else
			++conditionIter;
	}

	D3DXMATRIXA16 worldMat = GetWorldMatrix();

	if (m_pStateMachine)
		m_pStateMachine->Update();

	if (m_chrSkinnedMesh) 
	{
		m_chrSkinnedMesh->SetWorldMatrix(worldMat);
		m_chrSkinnedMesh->Update();
	}
		
	if (m_objSkinnedMesh) 
	{
		m_objSkinnedMesh->SetWorldMatrix(worldMat);
		m_objSkinnedMesh->Update();
	}
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

void cGameObject::SetStateMachine(cStateMachine* _pStateMachine)
{
	m_pStateMachine = _pStateMachine;
}

cStateMachine* cGameObject::GetStateMachine()
{
	return m_pStateMachine;
}

const BoundingSphere& cGameObject::GetBoundSphere()
{
	return m_sphere;
}

const BoundingBox & cGameObject::GetBoundBox()
{
	return m_box;
}

void cGameObject::OnMessage(const ST_PACKET & _packet)
{
	if (m_pStateMachine)
	{
		m_pStateMachine->MessageHandle(_packet);
	}
}

cAction * cGameObject::GetAction()
{
	return m_pAction;
}

void cGameObject::SetBoundSphere(const BoundingSphere & _sphere)
{
	m_sphere.fRadius=_sphere.fRadius;
	m_sphere.vCenter = _sphere.vCenter;
}

void cGameObject::SetBoundBox(const BoundingBox & _box)
{
	m_box.vMax = _box.vMax;
	m_box.vMin = _box.vMin;
}
