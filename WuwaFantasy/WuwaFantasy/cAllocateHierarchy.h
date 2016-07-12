#pragma once

class cMtlTex;

struct ST_BONE : public D3DXFRAME
{
	//D3DXMATRIX matWorldTM;
	D3DXMATRIX CombinedTransformationMatrix;
};

struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	std::vector<cMtlTex*>	vecMtlTex;
	LPD3DXMESH				pOrigMesh;				// ｿｻ ｸﾞｽｬ

	LPD3DXMESH				pWorkMesh;				// ﾀﾛｾ・ｸﾞｽｬ CloneMeshFVFｷﾎ ｺｹｻ・
	D3DXMATRIX**			ppBoneMatrixPtrs;		// ﾀﾌ ｸﾞｽｬｿ｡ ｿｵﾇ簑ｻ ﾁﾖｴﾂ ﾇﾁｷｹﾀﾓ'ｵ・ﾀﾇ ｿ蟶ﾅﾆｮｸｯｽｺ ﾆﾎﾅﾍ ｹ霑ｭ
	D3DXMATRIX*				pBoneOffsetMatrices;	// ｿｻ ｸﾞｽｬｸｦ ｷﾎﾄﾃｽｺﾆ菎ﾌｽｺｷﾎ ｺｸｳｻｴﾂ ｸﾅﾆｮｸｯｽｺｵ・
	D3DXMATRIX*				pCurrentBoneMatrices;	// ｰ｢ ｺｻﾀﾇ ｰ霆・?ｿ蟶ﾅﾆｮｸｯｽｺ
};

class cAllocateHierarchy : public ID3DXAllocateHierarchy
{
protected:
	std::string m_sFolder;

public:
	cAllocateHierarchy(void);
	~cAllocateHierarchy(void);

	void SetFolder(std::string sFolder) { m_sFolder = sFolder; }

	// ID3DXAllocateHierarchy

	//------------------------------------------------------------------------
	// CreateFrame:
	// ------------
	// Requests allocation of a frame object.
	//
	// Parameters:
	//  Name
	//		Name of the frame to be created
	//	ppNewFrame
	//		Returns the created frame object
	//
	//------------------------------------------------------------------------
	STDMETHOD(CreateFrame)(THIS_ LPCSTR Name, 
		LPD3DXFRAME *ppNewFrame);

	//------------------------------------------------------------------------
	// CreateMeshContainer:
	// --------------------
	// Requests allocation of a mesh container object.
	//
	// Parameters:
	//  Name
	//		Name of the mesh
	//	pMesh
	//		Pointer to the mesh object if basic polygon data found
	//	pPMesh
	//		Pointer to the progressive mesh object if progressive mesh data found
	//	pPatchMesh
	//		Pointer to the patch mesh object if patch data found
	//	pMaterials
	//		Array of materials used in the mesh
	//	pEffectInstances
	//		Array of effect instances used in the mesh
	//	NumMaterials
	//		Num elements in the pMaterials array
	//	pAdjacency
	//		Adjacency array for the mesh
	//	pSkinInfo
	//		Pointer to the skininfo object if the mesh is skinned
	//	pBoneNames
	//		Array of names, one for each bone in the skinned mesh. 
	//		The numberof bones can be found from the pSkinMesh object
	//	pBoneOffsetMatrices
	//		Array of matrices, one for each bone in the skinned mesh.
	//
	//------------------------------------------------------------------------
	STDMETHOD(CreateMeshContainer)(THIS_ 
		LPCSTR Name, 
		CONST D3DXMESHDATA *pMeshData, 
		CONST D3DXMATERIAL *pMaterials, 
		CONST D3DXEFFECTINSTANCE *pEffectInstances, 
		DWORD NumMaterials, 
		CONST DWORD *pAdjacency, 
		LPD3DXSKININFO pSkinInfo, 
		LPD3DXMESHCONTAINER *ppNewMeshContainer);

	//------------------------------------------------------------------------
	// DestroyFrame:
	// -------------
	// Requests de-allocation of a frame object.
	//
	// Parameters:
	//  pFrameToFree
	//		Pointer to the frame to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD(DestroyFrame)(THIS_ LPD3DXFRAME pFrameToFree); 

	//------------------------------------------------------------------------
	// DestroyMeshContainer:
	// ---------------------
	// Requests de-allocation of a mesh container object.
	//
	// Parameters:
	//  pMeshContainerToFree
	//		Pointer to the mesh container object to be de-allocated
	//
	//------------------------------------------------------------------------
	STDMETHOD(DestroyMeshContainer)(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree); 
};

