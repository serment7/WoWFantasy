#pragma once
#include "cAllocateHierarchy.h"

class cSkinnedMesh
{
public:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;
	ST_BONE*					m_pRightHand;
			
public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Load(const char* szFolder, const char* szFile);
	void Update();
	void Render(LPD3DXFRAME pFrame);
	void Release();
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	bool CompuseBoneName(char* str1, char* str2);
	ST_BONE* GetBoneNamedMesh(ST_BONE* pBone, char* szBoneName);

private:
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

	LPD3DXANIMATIONCONTROLLER GetAnimationController();

};

