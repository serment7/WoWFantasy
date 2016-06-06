
#pragma once
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"

enum EN_WEAPON_TYPE
{
	LEFT_HAND_WEAPON = 0x1000,		//왼손무콅E
	RIGHT_HAND_WEAPON,				//오른손무콅E
	LEFT_HAND_SHILED,				//방패
	HEAD_BOWL,						//투구
	WEAPON_NULL						//4000
};

class cWeaponSkinnedMesh
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;

	cSkinnedMesh*				m_pSkinnedMesh;
	ST_BONE*					m_pConnect;

public:
	cWeaponSkinnedMesh();
	~cWeaponSkinnedMesh();

	void Load(char* szFolder, char* szFile, EN_WEAPON_TYPE enWeaponType, cSkinnedMesh* pSkinndeMesh);
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
