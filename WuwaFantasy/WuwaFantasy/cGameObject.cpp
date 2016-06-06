
#include "stdafx.h"
#include "cGameObject.h"
#include "cCondition.h"
#include "cIAction.h"

cGameObject::cGameObject()
{
	g_pObjectManager->AddObject(this);
	D3DXCreateSphere(g_pD3DDevice, 2, 10, 10, &m_sphere, NULL);
	ST_STATUS status;
	ZeroMemory(&status, sizeof(status));
	status.fSpeed = 1.0f;
	m_pStatus.Setup(status);
}

cGameObject::~cGameObject()
{
	SAFE_RELEASE(m_sphere);
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

	if (m_pStateMachine)
		m_pStateMachine->Update();

	if (m_pAction)
	{
		m_pAction->Update();

		if (!m_pAction->IsLifeTime())
		{
			SAFE_DELETE(m_pAction);
		}
	}
		

	D3DXMATRIXA16 worldMat = GetWorldMatrix();

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

LPD3DXMESH cGameObject::GetBound()
{
	return m_sphere;
}

void cGameObject::OnMessage(const ST_PACKET & _packet)
{
	if (m_pStateMachine)
	{
		m_pStateMachine->MessageHandle(_packet);
	}
}

void cGameObject::SetAction(cIAction * _action)
{
	m_pAction = _action;
}

cIAction * cGameObject::GetAction()
{
	return m_pAction;
}
