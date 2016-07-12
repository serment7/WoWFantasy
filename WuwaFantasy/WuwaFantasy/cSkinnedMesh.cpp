#include "StdAfx.h"
#include "cSkinnedMesh.h"
#include "cMtlTex.h"

cSkinnedMesh::cSkinnedMesh(void)
	: m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fAnimBlendTime(0.3f)
	, m_fPassedAnimBlendTime(0.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cSkinnedMesh::~cSkinnedMesh(void)
{
	cAllocateHierarchy alloc;
	D3DXFrameDestroy(m_pRoot, &alloc);
}

void cSkinnedMesh::Load( const char* szFile )
{
	std::string sFile(szFile);
	std::string sFullPath = m_folderName +"/"+ sFile;
	LPD3DXFRAME pFrame = NULL;
	cAllocateHierarchy* alloc=new cAllocateHierarchy;

	alloc->SetFolder(m_folderName);
	LPDIRECT3DDEVICE9 d = g_pD3DDevice;
	D3DXLoadMeshHierarchyFromXA(
		sFullPath.c_str(),
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		alloc,
		NULL,
		&m_pRoot,
		&m_pAnimController);
	SAFE_DELETE(alloc);
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

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(pBone->CombinedTransformationMatrix*m_matWorld));
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

void cSkinnedMesh::Release()
{
	this->~cSkinnedMesh();
}

void cSkinnedMesh::SetupBoneMatrixPtrs( LPD3DXFRAME pFrame )
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
				//std::cout<<pSkinInfo->GetBoneName(i)<<std::endl;
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

const float cSkinnedMesh::GetAnimationPeriod(const UINT& _index)
{
	m_pAnimController->GetAnimationSet(_index,&m_pAniSet);
	float fPeriod= m_pAniSet->GetPeriod();
	SAFE_RELEASE(m_pAniSet);
	return fPeriod;
}

LPD3DXANIMATIONCONTROLLER cSkinnedMesh::GetAnimationController()
{
	return m_pAnimController;
}

const std::string & cSkinnedMesh::GetFolderName()
{
	return m_folderName;
}

void cSkinnedMesh::SetFolderName(const std::string & _name)
{
	m_folderName = _name;
}

void cSkinnedMesh::UpdateSkinnedMesh( LPD3DXFRAME pFrame )
{
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
				pBoneMesh->pCurrentBoneMatrices[i] =
					pBoneMesh->pBoneOffsetMatrices[i] *
					*(pBoneMesh->ppBoneMatrixPtrs[i]);
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

void cSkinnedMesh::SetAnimationIndex( int nIndex )
{
	m_pAnimController->GetAnimationSet(nIndex, &m_pAniSet);
	m_pAnimController->SetTrackAnimationSet(0, m_pAniSet);
	SAFE_RELEASE(m_pAniSet);
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

bool cSkinnedMesh::CompuseBoneName(char* str1,const char* str2)
{
	char* temp = NULL;
	char* context = NULL; //The Pointer is Using inside at strtok_s Function

	temp = strtok_s(str1, "_", &context);

	while(true)
	{
		if(temp == NULL) return false;
		int i = strlen(temp);
		int j = strlen(str2);

		if(i == j && !strncmp(temp, str2, j)) break;
		
		temp = strtok_s(NULL, "_", &context);
	}

	return true;
}

ST_BONE* cSkinnedMesh::GetBoneNamedMesh(ST_BONE* pBone,char* szBoneName)
{
	ST_BONE* pFrame = NULL;
	ST_BONE* frame = NULL;
	std::string name(szBoneName);
	if (pBone)
		pFrame = (ST_BONE*)pBone;
	else
		pFrame = (ST_BONE*)m_pRoot;
	
	if (pFrame->Name && CompuseBoneName(pFrame->Name, szBoneName))
		return pFrame;

	if (pFrame->pFrameSibling)
	{
		frame = GetBoneNamedMesh((ST_BONE*)pFrame->pFrameSibling, szBoneName);
		if (frame && !CompuseBoneName(frame->Name, szBoneName))
			return frame;
	}

	if (pFrame->pFrameFirstChild)
	{
		frame=GetBoneNamedMesh((ST_BONE*)pFrame->pFrameFirstChild, szBoneName);
		if (frame && !CompuseBoneName(frame->Name, szBoneName))
			return frame;
	}
	return NULL;

}

void cSkinnedMesh::SetWorldMatrix(const D3DXMATRIXA16 & _matWorld)
{
	m_matWorld = _matWorld;
}

const D3DXMATRIXA16 & cSkinnedMesh::GetWorldMatrix()
{
	return m_matWorld;
}
