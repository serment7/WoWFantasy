
#include "stdafx.h"
#include "cSkinnedMash.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"


cSkinnedMash::cSkinnedMash()
:	m_pRoot(NULL)
,	m_pAnimController(NULL)
,	m_fAnimBlendTime(0.3f)
,	m_fPassedAnimBlendTime(0.0f)
{

}

cSkinnedMesh::~cSkinnedMash()
{
	cAllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRoot, &alloc);
}

void cSkinnedMesh::Load