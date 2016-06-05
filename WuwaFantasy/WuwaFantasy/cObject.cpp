
#include "stdafx.h"
#include "cObject.h"
#include <assert.h>

cObject::cObject()
:	nRefCount(0)
,	m_vPos(0, 0, 0)
,	m_vDir(0, 0, 1)
{
	g_pObjectManager->AddObject(this);
}

cObject::~cObject()
{
	assert(nRefCount>=0&&"��ü �Ҹ��� ������ �Ͼ���ֽ��ϴ�");
}

void cObject::SetID(const size_t & _id)
{
	m_unID = _id;
}

void cObject::SetTag(const size_t & _tag)
{
	m_unTag = _tag;
}

const size_t & cObject::GetID()
{
	return m_unID;
}

const size_t & cObject::GetTag()
{
	return m_unTag;
}

void cObject::AddRef()
{
	++nRefCount;
}

void cObject::Release()
{
	--nRefCount;
	if(nRefCount <= 0)
	{
		g_pObjectManager->RemoveObject(this);
		delete this;
	}
}

void cObject::Update()
{
	//�ۿ��� vPos�� vDir�� �޾Ƽ� ���õǾ�E�ִ� ���¿��� �軁E?
	D3DXMATRIXA16 matWorld;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = m_matS * m_matR * m_matT;

	m_matWorld = matWorld;
}

void cObject::SetRotationY(const float & _angle)
{
	m_angleY = _angle;
}

void cObject::TurnRotationY(const float & _angle)
{
	m_angleY += _angle;
}

const float & cObject::GetRotationY() const
{
	return m_angleY;
}