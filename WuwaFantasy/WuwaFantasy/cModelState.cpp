#include "stdafx.h"
#include "cModelState.h"
#include "cGameObject.h"

cModelState::cModelState()
{
}


cModelState::~cModelState()
{
}


void cModelState::SetupAnimation(const int & index)
{
	if (m_nCurAni == index)
		return;
	m_nCurAni = index;
	m_pOwner->GetChrSkinnedMesh()->SetAnimationIndexBlend(m_nCurAni);
	m_pAniController->GetAnimationSet(m_nCurAni, &m_pAniSet);
	m_fPeriod = (float)m_pAniSet->GetPeriod();
	m_pAniController->SetTrackPosition(0, 0.0f);
}
