
#include "stdafx.h"
#include "cObject.h"
#include <assert.h>

cObject::cObject()
:	nRefCount(0)
,	m_vPos(0, 0, 0)
,	m_vDir(0, 0, 1)
{
	//ｿﾀｺ・ｧﾆｮ ｸﾅｴﾏﾀ・ﾃﾟｰ｡
}

cObject::~cObject()

{
	//ｿﾀｺ・ｧﾆｮ ｸﾅｴﾏﾀ・ｻ霖ｦ
#ifdef _DEBUG
	assert(nRefCount <= 0 && "ﾇﾘﾁｦ ｵﾈ ｿﾀｺ・ｧﾆｮｸｦ ﾇﾑｹ・ｴ・ﾇﾘﾁｦﾇﾕｴﾏｴﾙ");
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
	//ｹﾛｿ｡ｼｭ vPosｿﾍ vDirﾀｻ ｹﾞｾﾆｼｭ ｼﾂﾆﾃｵﾇｾ・ﾀﾖｴﾂ ｻﾂｿ｡ｼｭ ｰ霆・ﾊ
	D3DXMATRIXA16 matWorld;

	D3DXMatrixTranslation(&m_matT, m_vPos.x, m_vPos.y, m_vPos.z);
	matWorld = m_matS * m_matR * m_matT;

	m_matWorld = matWorld;
}