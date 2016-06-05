#pragma once
#include "cIAction.h"
class cActionMove :
	public cIAction
{
private:
	D3DXVECTOR3		m_vFrom;
	D3DXVECTOR3		m_vTo;

public:
	cActionMove();
	virtual ~cActionMove();
	void			SetFrom(const D3DXVECTOR3&);
	void			SetTo(const D3DXVECTOR3&);
	virtual void	Start();
	virtual void	Update();
	virtual void	Stop();
};

