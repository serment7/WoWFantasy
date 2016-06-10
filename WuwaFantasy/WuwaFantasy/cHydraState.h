#pragma once
#include "cIState.h"

class cStatus;
class cSkinnedMesh;
class cWeaponSkinnedMesh;

class cHydraState :
	public cIState
{
private:
	cGameObject*				m_pOwner;
	LPD3DXANIMATIONCONTROLLER	m_pAniController;
	D3DXTRACK_DESC				m_desc;
	LPD3DXANIMATIONSET			m_pAniSet;
	cSkinnedMesh*				m_chrmesh=nullptr;

	double						m_fPeriod=0.0f;
	double						m_fCurPeriod = 0.0f;
	int							m_nCurAni=0;
	bool						m_bLive=true;
public:
	cHydraState();
	~cHydraState();

	virtual void	EnterState(cGameObject* _entity);
	virtual void	ExitState(cGameObject* _entity);
	virtual void	Execute(cGameObject* _entity);
	virtual bool	OnMessage(cGameObject* _entity, const ST_PACKET& _packet);
	void			SetupAnimation(const int& index);
};

