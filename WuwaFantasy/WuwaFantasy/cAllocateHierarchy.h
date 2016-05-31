
#pragma once

class cMtlTex;

struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIX CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<cMtlTex*>	vecMtlTex;	
	LPD3DXMESH				pOrigMesh;				// ���� �޽�

	LPD3DXMESH				pWorkMesh;				// �۾� �޽� CloneMeshFVF�� ����
	D3DXMATRIX**			ppBoneMatrixPtrs;		// �� �޽��� ������ �ִ� ������'��'�� �����Ʈ���� ������ �迭
	D3DXMATRIX*				pBoneOffsetMatrices;	// ���� �޽��� ���ý����̽��� ������ ��Ʈ������.
	D3DXMATRIX*				pCurrentBoneMatrices;	// �� ���� ���� �����Ʈ����
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
