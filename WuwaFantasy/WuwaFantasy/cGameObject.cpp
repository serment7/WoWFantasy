#include "stdafx.h"
#include "cGameObject.h"
#include "cCondition.h"
#include "cAction.h"

cGameObject::cGameObject()
	:m_pAction(new cAction(this))
{
	ZeroMemory(&m_sphere, sizeof(m_sphere));
	ZeroMemory(&m_box, sizeof(m_box));
}

cGameObject::cGameObject(const std::string& _Folder, const std::string & _ModelPath)
{
	this->AddRef();
	m_pAction = new cAction(this);
	m_chrSkinnedMesh = new cSkinnedMesh;
	m_chrSkinnedMesh->SetFolderName(_Folder);
	m_chrSkinnedMesh->Load(_ModelPath.c_str());
	m_objSkinnedMesh = nullptr;
	SetVBaseDir(D3DXVECTOR3(0, 0, -1));
	SetVDir(D3DXVECTOR3(0, 0, -1));

	ST_STATUS status;
	ZeroMemory(&status,sizeof(status));
	m_pStatus.Setup(status);

	SetTag(g_pGameManager->FindObjectType("thrown"));
	g_pObjectManager->AddObject(this);
}

cGameObject::~cGameObject()
{
	auto conditionIter = m_listCondition.begin();
	while (conditionIter != m_listCondition.end())
	{
		SAFE_DELETE((*conditionIter));
		m_listCondition.erase(conditionIter++);
	}
	SAFE_DELETE(m_chrSkinnedMesh);
	SAFE_DELETE(m_objSkinnedMesh);
	SAFE_DELETE(m_pStateMachine);
	g_pObjectManager->RemoveObject(this);
}

void cGameObject::Update()
{
	
	static bool bDeleteCondition = false;
	float delta = g_pTimeManager->GetDeltaTime();

	auto conditionIter = m_listCondition.begin();
	while (conditionIter != m_listCondition.end())
	{
		(*conditionIter)->Update(delta,bDeleteCondition);
		if (bDeleteCondition)
		{
			SAFE_DELETE(*conditionIter);
			m_listCondition.erase(conditionIter++);
		}
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
	cObject::Update();

	if (m_objSkinnedMesh) 
	{
		m_objSkinnedMesh->SetWorldMatrix(worldMat);
		m_objSkinnedMesh->Update();
	}
}

void cGameObject::Render()
{
	if (m_bShow)
	{
		
		if (m_chrSkinnedMesh)
			m_chrSkinnedMesh->Render(NULL);

		if (m_objSkinnedMesh)
			m_objSkinnedMesh->Render(NULL);

		if (!m_listCondition.empty())
		{
			auto conditionIter = m_listCondition.begin();
			while (conditionIter != m_listCondition.end())
			{
				(*conditionIter)->Render();
				++conditionIter;
			}
		}
	}
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

BoundingSphere cGameObject::GetBoundSphere()
{
	BoundingSphere sphere;
	sphere.fRadius = m_sphere.fRadius;
	sphere.vCenter = m_sphere.vCenter + GetVPos();
	return sphere;
}

BoundingBox& cGameObject::GetBoundBox()
{
	return m_box;
}

void cGameObject::OnMessage(const ST_PACKET & _packet)
{
	if (m_pStateMachine)
	{
		switch (_packet.msg_type)
		{
		case Msg_Render:
			auto conditionIter = m_listCondition.begin();
			while (conditionIter != m_listCondition.end())
			{
				(*conditionIter)->PostRender();
				++conditionIter;
			}
			break;
		}
		m_pStateMachine->MessageHandle(_packet);
	}
}

cAction * cGameObject::GetAction()
{
	return m_pAction;
}

void cGameObject::SetBoundSphere(const float& _fRadius, const D3DXVECTOR3& _vCenters)
{
	BoundingSphere sphere(_vCenters,_fRadius);
	m_sphere=sphere;
}

void cGameObject::SetBoundBox(const D3DXVECTOR3& _max, const D3DXVECTOR3& _min)
{
	BoundingBox box(_min, _max);
	m_box=box;
}

void cGameObject::SetName(const std::string & _name)
{
	m_name = _name;
}

const std::string & cGameObject::GetName() const
{
	return m_name;
}

void cGameObject::SetShow(bool _show)
{
	m_bShow = _show;
}

bool cGameObject::IsShow()
{
	return m_bShow;
}
