
#pragma once

class cSkinnedMesh  
{
private:
	LPD3DXFRAME					m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	float						m_fAnimBlendTime;
	float						m_fPassedAnimBlendTime;
			
public:
	cSkinnedMesh();
	~cSkinnedMesh();

	void Load(char* szFolder, char* szFile);
	void Update();
	void Render(LPD3DXFRAME pFrame);

	//에니메이션 컨트롤러
	void SetAnimation(str::string szMotionName);


private:
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void SetAnimationIndex(int nIndex);
	void SetAnimationIndexBlend(int nIndex);
};