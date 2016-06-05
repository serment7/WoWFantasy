
#include "stdafx.h"
#include "cObject.h"
#include <assert.h>

cObject::cObject()
:	nRefCount(0)
,	m_vPos(0, 0, 0)
,	m_vDir(0, 0, 1)
{
	//����E�Ʈ �Ŵ���E�߰�
}

cObject::~cObject()

{
	//����E�Ʈ �Ŵ���E����
#ifdef _DEBUG
	assert(nRefCount <= 0 && "���� �� ����E�Ʈ�� �ѹ�E��E�����մϴ�");
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

void cObject::Update()
{
	//�ۿ��� vPos�� vDir�� �޾Ƽ� ���õǾ�E�ִ� ���¿��� �軁E�
	D3DXMATRIXA16 matWorld;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = m_matS * m_matR * m_matT;

	m_matWorld = matWorld;
}