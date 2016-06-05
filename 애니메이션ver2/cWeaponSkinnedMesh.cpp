
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

	if(m_pSkinnedMesh) m_pConnect = pSkinnedMesh->GetBoneNamedMesh(NULL, "humanfemale_Bone46_RFingerRing");

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
	// pCurrentBoneMatrices �� ����Ͻÿ�
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

			//MeshData.pMesh�� ������Ʈ �����ش�.
			pSkinInfo->UpdateSkinnedMesh(
				pBoneMesh->pCurrentBoneMatrices, NULL, src, dest );

			pBoneMesh->pWorkMesh->UnlockVertexBuffer();
			pBoneMesh->pOrigMesh->UnlockVertexBuffer();
		}
	}

	//��������� ��� �����ӿ� ���ؼ� ����.
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
	// �� �������� �޽� �����̳ʿ� �ִ� pSkinInfo�� �̿��Ͽ� ����޴� ��� 
	// �������� ��Ʈ������ ppBoneMatrixPtrs�� �����Ѵ�.
	// pSkinInfo->GetNumBones() ���� ����޴� ���� ������ ã��.
	// pSkinInfo->GetBoneName(i) �� i�� �������� �̸��� ã��
	// D3DXFrameFind(��Ʈ ������, ������ �̸�) �� �������� ã��.
	// ã�Ƽ� �����Ʈ������ �ɾ����.

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

	//��������� ��� �����ӿ� ���ؼ� ����.
	if (pFrame->pFrameFirstChild)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);
	}

	if (pFrame->pFrameSibling)
	{
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	}
}
