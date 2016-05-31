
#pragma once

class cMtlTex;

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<cMtlTex*>	vecMtlTex;	
	LPD3DXMESH				pOrigMesh;				// 원본 메쉬

	LPD3DXMESH				pWorkMesh;				// 작업 메쉬 CloneMeshFVF로 복사
	D3DXMATRIX**			ppBoneMatrixPtrs;		// 이 메쉬에 영향을 주는 프레임'들'의 월드매트릭스 포인터 배열
	D3DXMATRIX*				pBoneOffsetMatrices;	// 원본 메쉬를 로컬스페이스로 보내는 매트릭스들.
	D3DXMATRIX*				pCurrentBoneMatrices;	// 각 본의 계산된 월드매트릭스
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
private:
	std::string m_sFolder;
public:
	cAllocateHierarchy();
	virtual ~cAllocateHierarchy();

	//Redifinition
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame);

	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree); 

	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree); 

};
