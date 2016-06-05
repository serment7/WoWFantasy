
#include "stdafx.h"
#include "cWeaponSkinnedMesh.h"
#include "cMtlTex.h"


cWeaponSkinnedMesh::cWeaponSkinnedMesh()
{

}

cWeaponSkinnedMesh::~cWeaponSkinnedMesh()
{

}

void cWeaponSkinnedMesh::Load(char* szFolder, char* szFile, EN_WEAPON_TYPE enWeaponType, cSkinnedMesh* pSkinnedMesh)
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

	m_pSkinnedMesh = pSkinnedMesh;

	if(m_pSkinnedMesh) m_pConnect = pSkinnedMesh->GetBoneNamedMesh(NULL, "RFingerRing");

	SetupBoneMatrixPtrs(m_pRoot);
}

void cWeaponSkinnedMesh::Update()
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

	Update(m_pRoot, m_pConnect);
	UpdateSkinnedMesh(m_pRoot);
}

void cWeaponSkinnedMesh::Update(LPD3DXFRAME pFrame, ST_BONE* pParent)
{
	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pFrame->TransformationMatrix;
	if (pParent)
	{
		pBone->CombinedTransformationMatrix *= pParent->CombinedTransformationMatrix;
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

void cWeaponSkinnedMesh::Render(LPD3DXFRAME pFrame)
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

void cWeaponSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	D3DXMATRIX matS;
	D3DXMatrixScaling(&matS, 0.5f, 0.5f, 0.5f);
	// pCurrentBoneMatrices ｸｦ ｰ霆・ﾏｽﾃｿ?
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
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * matS;
			}

			BYTE* src = NULL;
			BYTE* dest = NULL;

			pBoneMesh->pOrigMesh->LockVertexBuffer( D3DLOCK_READONLY, (void**)&src );
			pBoneMesh->pWorkMesh->LockVertexBuffer( 0, (void**)&dest );

			//MeshData.pMeshﾀｻ ｾ･ﾀﾌﾆｮ ｽﾃﾄﾑﾁﾘｴﾙ.
			pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

			pBoneMesh->pWorkMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	//ﾀ邀ﾍﾀ釥ｸｷﾎ ｸ・ﾇﾁｷｹﾀﾓｿ｡ ｴ・ﾘｼ?ｽﾇ?E
	if (pFrame->pFrameFirstChild)
	{
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		UpdateSkinnedMesh(pFrame->pFrameSibling);
	}
}
void cWeaponSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	// ｰ｢ ﾇﾁｷｹﾀﾓﾀﾇ ｸﾞｽﾃ ﾄﾁﾅﾗﾀﾌｳﾊｿ｡ ﾀﾖｴﾂ pSkinInfoｸｦ ﾀﾌｿ・ﾏｿ?ｿｵﾇ篁ﾞｴﾂ ｸ・
	// ﾇﾁｷｹﾀﾓﾀﾇ ｸﾅﾆｮｸｯｽｺｸｦ ppBoneMatrixPtrsｿ｡ ｿｬｰ睇ﾑｴﾙ.
	// pSkinInfo->GetNumBones() ﾀｸｷﾎ ｿｵﾇ篁ﾞｴﾂ ｺｻﾀﾇ ｰｳｼｦ ﾃ｣ﾀｽ.
	// pSkinInfo->GetBoneName(i) ｷﾎ iｹ・ﾇﾁｷｹﾀﾓﾀﾇ ﾀﾌｸｧﾀｻ ﾃ｣ﾀｽ
	// D3DXFrameFind(ｷ酥ｮ ﾇﾁｷｹﾀﾓ, ﾇﾁｷｹﾀﾓ ﾀﾌｸｧ) ｷﾎ ﾇﾁｷｹﾀﾓﾀｻ ﾃ｣ﾀｽ.
	// ﾃ｣ｾﾆｼｭ ｿ蟶ﾅﾆｮｸｯｽｺｸｦ ｰﾉｾ錝犖・

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

	//ﾀ邀ﾍﾀ釥ｸｷﾎ ｸ・ﾇﾁｷｹﾀﾓｿ｡ ｴ・ﾘｼ?ｽﾇ?E
	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}

void cWeaponSkinnedMesh::SetAnimationIndex( int nIndex )
{
	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet);
	SAFE_RELEASE(pAnimSet);
}

void cWeaponSkinnedMesh::SetAnimationIndexBlend( int nIndex )
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
