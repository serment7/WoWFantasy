
#include "stdafx.h"
#include "cObject.h"
#include "cStateMachine.h"
#include"cCondition.h"

cObject::cObject()
	: m_vPos(0, 0, 0)
	, m_vDir(0, 0, 1)
{

}

cObject::~cObject()
{
	assert(nRefCount>=0&&"객체 소멸이 여러번 일어나고있습니다");
}

void cObject::Update()
{
	//밖에서 vPos와 vDir을 받아서 셋팅되푳E있는 상태에서 계퍊E?
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
