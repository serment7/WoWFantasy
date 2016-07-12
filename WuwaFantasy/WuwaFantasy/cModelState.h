#pragma once
#include "cIState.h"

class cSkinnedMesh;

class cModelState :
	public cIState
{
protected:
	cGameObject*				m_pOwner = nullptr;
	size_t						m_entityID = MAXSIZE_T;

	LPD3DXANIMATIONCONTROLLER	m_pAniController = nullptr;
	D3DXTRACK_DESC				m_desc;
	LPD3DXANIMATIONSET			m_pAniSet = nullptr;
	cSkinnedMesh*				m_chrmesh = nullptr;

	float						m_fPeriod = 0.0f;
	float						m_fCurPeriod = 0.0f;
	int							m_nCurAni = 0;
	float						m_fPassedAnitime;
public:
	cModelState();
	~cModelState();
	void				SetupAnimation(const int& index);
};

