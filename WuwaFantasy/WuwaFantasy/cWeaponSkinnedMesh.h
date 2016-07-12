
#pragma once
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"

//enum EN_WEAPON_TYPE
//{
//	LEFT_HAND_WEAPON = 0x1000,		//왼손무콅E
//	RIGHT_HAND_WEAPON,				//오른손무콅E
//	LEFT_HAND_SHILED,				//방패
//	HEAD_BOWL,						//투구
//	WEAPON_NULL						//4000
//};

class cWeaponSkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;

	cSkinnedMesh*				m_pSkinnedMesh=nullptr;
	ST_BONE*					m_pConnect;

	D3DXMATRIXA16 parentMat;

public:
	cWeaponSkinnedMesh();
	~cWeaponSkinnedMesh();

	void Load(const char* szFolder, const char* szFile, cSkinnedMesh* pSkinndeMesh,char* _connectPart);
	void Update();
	void Render(LPD3DXFRAME pFrame);
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	void SetWorldMatrix(const D3DXMATRIXA16& _matWorld);

private:
	void Update(LPD3DXFRAME pFrame, ST_BONE* pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

};
