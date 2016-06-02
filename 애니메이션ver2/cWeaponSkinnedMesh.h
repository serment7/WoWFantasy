
#pragma once
#include "cAllocateHierarchy.h"
#include "cSkinnedMesh.h"

enum EN_WEAPON_TYPE
{
	LEFT_HAND_WEAPON = 1000,		//왼손무기
	RIGHT_HAND_WEAPON,				//오른손무기
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
	void Setup(D3DXFRAME* pFrame, EN_WEAPON_TYPE enWeaponType);
	void Update();
	void Render(LPD3DXFRAME pFrame);

private:
	void Update(LPD3DXFRAME pFrame, ST_BONE* pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

};
