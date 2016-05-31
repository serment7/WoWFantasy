
#include "stdafx.h"
#include "cSkinnedMesh.h"


cSkinnedMesh::cSkinnedMesh()
: m_pRoot(NULL)
, m_pAnimController(NULL)
, m_fAnimBlendTime(0.3f)
, m_fPassedAnimBlendTime(0.0f)
{

}

cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRoot, &alloc)
}

void cSkinnedMesh::Load( char* szFolder, char* szFile )
{
	std::string sFolder(szFolder);
	std::string sFile(szFile);
	std::string sFullPath = szFolder + std::string("/") + sFile;
	LPD3DXFRAME pFrame = NULL;
	cAllocateHierarchy alloc;
	alloc.SetFolder(sFolder);

	D3DXLoadMeshHierarchyFromX(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&alloc,
		NULL,
		&m_pRoot,
		&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);
}

void cSkinnedMesh::Update( LPD3DXFRAME pFrame, LPD3DXFRAME pParent )
{
	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	if (pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}
	if (pBone->pFrameFirstChild)
	{
		Update(pBone->pFrameFirstChild, pBone);
	}
	if (pBone->pFrameSibling)
	{
		Update(pBone->pFrameSibling, pParent);
	}
}

void cSkinnedMesh::Update()
{
	m_pAnimController->AdvanceTime(g_pTimeManager->GetDeltaTime(), NULL);

	if (m_fPassedAnimBlendTime < m_fAnimBlendTime)
	{
		m_fPassedAnimBlendTime += g_pTimeManager->GetDeltaTime();
		if (m_fPassedAnimBlendTime > m_fAnimBlendTime)
		{
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false);
		}
		else
		{
			float f = m_fPassedAnimBlendTime / m_fAnimBlendTime;
			m_pAnimController->SetTrackWeight(0, f);
			m_pAnimController->SetTrackWeight(1, 1 - f);
		}
	}

	Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);
}

void cSkinnedMesh::Render( LPD3DXFRAME pFrame )
{
	ST_BONE* pBone = NULL;
	
	if(pFrame)
		pBone = (ST_BONE*)pFrame;
	else
		pBone = (ST_BONE*)m_pRoot;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
	if(pBoneMesh)
	{
		for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
		{
			g_pD3DDevice->SetMaterial(&pBoneMesh->vecMtlTex[i]->GetMtl());
			g_pD3DDevice->SetTexture(0, pBoneMesh->vecMtlTex[i]->GetTexture());
			pBoneMesh->pWorkMesh->DrawSubset(i);
		}
	}
	if (pBone->pFrameFirstChild)
	{
		Render(pBone->pFrameFirstChild);
	}
	if (pBone->pFrameSibling)
	{
		Render(pBone->pFrameSibling);
	}
}

void cSkinnedMesh::SetupBoneMatrixPtrs( LPD3DXFRAME pFrame )
{
	// 각 프레임의 메시 컨테이너에 있는 pSkinInfo를 이용하여 영향받는 모든 
	// 프레임의 매트릭스를 ppBoneMatrixPtrs에 연결한다.
	// pSkinInfo->GetNumBones() 으로 영향받는 본의 개수를 찾음.
	// pSkinInfo->GetBoneName(i) 로 i번 프레임의 이름을 찾음
	// D3DXFrameFind(루트 프레임, 프레임 이름) 로 프레임을 찾음.
	// 찾아서 월드매트릭스를 걸어줘라.

	if (pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &pBone->CombinedTransformationMatrix;
			}
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}

}

void cSkinnedMesh::UpdateSkinnedMesh( LPD3DXFRAME pFrame )
{
	// pCurrentBoneMatrices = pBoneOffsetMatrices * ppBoneMatrixPtrs 
	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;
		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for (DWORD i = 0; i < dwNumBones; ++i)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = 
					pBoneMesh->pBoneOffsetMatrices[i] *
					*(pBoneMesh->ppBoneMatrixPtrs[i]);
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
			pBoneMesh->pWorkMesh->LockVertexBuffer( 0, (void**)&dest );

			//MeshData.pMesh을 업데이트 시켜준다.
			pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

			pBoneMesh->pWorkMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	//재귀적으로 모든 프레임에 대해서 실행.
	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}

void cSkinnedMesh::SetAnimationIndex( int nIndex )
{
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}

void cSkinnedMesh::SetAnimationIndexBlend( int nIndex )
{
	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	
	D3DXTRACK_DESC stTrackDest;
	m_pAnimController->GetTrackDesc(0, &stTrackDest);
	m_pAnimController->SetTrackDesc(1, &stTrackDest);

	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet);

	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	SAFE_RELEASE(pPrevAnimSet);
	SAFE_RELEASE(pNextAnimSet);

	m_fPassedAnimBlendTime = 0.0f;
}

void cSkinnedMesh::SetAnimation(str::string szMotionName)
{
	int index = 0;
	LPD3DXANIMATIONSET pAnimSet;
	m_pAnimController->GetAnimationSet(
}