#include "StdAfx.h"
#include "cAllocateHierarchy.h"
#include "cMtlTex.h"

cAllocateHierarchy::cAllocateHierarchy(void)
{
}


cAllocateHierarchy::~cAllocateHierarchy(void)
{
}

STDMETHODIMP cAllocateHierarchy::CreateFrame( THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame )
{
	ST_BONE* pBone = new ST_BONE;
	D3DXMatrixIdentity(&pBone->CombinedTransformationMatrix);
	if (Name)
	{
		pBone->Name = new CHAR[strlen(Name) + 1];

		strcpy_s(pBone->Name, strlen(pBone->Name), Name);

	}
	else
	{
		pBone->Name = NULL;
	}
	
	
	*ppNewFrame = pBone;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::CreateMeshContainer( THIS_ LPCSTR Name, 
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials, 
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer )
{
	ST_BONE_MESH* pBoneMesh = new ST_BONE_MESH;
	ZeroMemory(pBoneMesh, sizeof(ST_BONE_MESH));


	pSkinInfo->AddRef();
	pBoneMesh->pSkinInfo = pSkinInfo;

	pBoneMesh->vecMtlTex.resize(NumMaterials);
	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		cMtlTex* pMtlTex = new cMtlTex;
		pMtlTex->SetMtl((D3DMATERIAL9)pMaterials[i].MatD3D);
		std::string sFullPath(pMaterials[i].pTextureFilename);
		sFullPath = m_sFolder + std::string("/") + sFullPath;
		pMtlTex->SetTexture((LPDIRECT3DTEXTURE9)g_pTextureManager->GetTexture(sFullPath));
		pBoneMesh->vecMtlTex[i] = pMtlTex;
	}
	pBoneMesh->pOrigMesh = pMeshData->pMesh;
	pBoneMesh->pOrigMesh->AddRef();

	pBoneMesh->pOrigMesh->CloneMeshFVF(pBoneMesh->pOrigMesh->GetOptions(),
		pBoneMesh->pOrigMesh->GetFVF(),
		g_pD3DDevice,
		&pBoneMesh->pWorkMesh);

	if(pSkinInfo)
	{
		DWORD dwNumBones = pSkinInfo->GetNumBones();
		pBoneMesh->ppBoneMatrixPtrs = new D3DXMATRIX*[dwNumBones];
		pBoneMesh->pBoneOffsetMatrices = new D3DXMATRIX[dwNumBones];
		pBoneMesh->pCurrentBoneMatrices = new D3DXMATRIX[dwNumBones];


		// pSkinInfo->GetBoneOffsetMatrix(i)
		for (DWORD i = 0; i < dwNumBones; ++i)
		{
			pBoneMesh->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}
	else
	{
		pBoneMesh->ppBoneMatrixPtrs = NULL;
		pBoneMesh->pBoneOffsetMatrices = NULL;
		pBoneMesh->pCurrentBoneMatrices = NULL;

	}

	*ppNewMeshContainer = pBoneMesh;
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyFrame( THIS_ LPD3DXFRAME pFrameToFree )
{
	//It is NOT loaded
	if (pFrameToFree && pFrameToFree->Name) {
		//SAFE_DELETE_ARRAY(pFrameToFree->Name);
	}

	SAFE_DELETE(pFrameToFree);
	
	return S_OK;
}

STDMETHODIMP cAllocateHierarchy::DestroyMeshContainer( THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree )
{
	ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pMeshContainerToFree;
	SAFE_RELEASE(pBoneMesh->pSkinInfo);
	SAFE_RELEASE(pBoneMesh->pOrigMesh);
	SAFE_RELEASE(pBoneMesh->pWorkMesh);

	SAFE_DELETE_ARRAY(pBoneMesh->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pBoneMesh->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pBoneMesh->pCurrentBoneMatrices);

	for (size_t i = 0; i < pBoneMesh->vecMtlTex.size(); ++i)
	{
		SAFE_RELEASE(pBoneMesh->vecMtlTex[i]);
	}
	return S_OK;
}
