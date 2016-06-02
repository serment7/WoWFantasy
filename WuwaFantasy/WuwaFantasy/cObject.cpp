
#include "stdafx.h"
#include "cObject.h"
#include <assert.h>

cObject::cObject()
:	nRefCount(1)
,	m_vPos(0, 0, 0)
,	m_vDir(0, 0, 1)
{
	//오브젝트 매니저 추가
}

cObject::~cObject()
{
	//오브젝트 매니저 삭제
#ifdef _DEBUG
	assert(nRefCount <= 0 && "해제 된 오브젝트를 한번 더 해제합니다");
#endif
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
		delete this;
	}
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

void cObject::Update()
{
	//밖에서 vPos와 vDir을 받아서 셋팅되어 있는 상태에서 계산됨
	D3DXMATRIXA16 matWorld;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = m_matS * m_matR * m_matT;

	m_matWorld = matWorld;
}