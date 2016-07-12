#pragma once
#include "cAllocateHierarchy.h"

class cSkinnedMesh
{
public:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	LPD3DXANIMATIONSET m_pAniSet = nullptr;

	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;
	ST_BONE*					m_pRightHand;

	std::string					m_folderName;
	D3DXMATRIXA16				m_matWorld;
	
			
public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Load( const char* szFile);
	void Update();
	void Render(LPD3DXFRAME pFrame);
	void Release();
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
	bool CompuseBoneName(char* str1, const char* str2);
	ST_BONE* GetBoneNamedMesh(ST_BONE* pBone, char* szBoneName);
	void SetWorldMatrix(const D3DXMATRIXA16& _matWorld);
	const D3DXMATRIXA16&		GetWorldMatrix();

	const std::string&			GetFolderName();
	void						SetFolderName(const std::string& _name);
	LPD3DXANIMATIONCONTROLLER	GetAnimationController();
	const float GetAnimationPeriod(const UINT& _index);

private:
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);

};
