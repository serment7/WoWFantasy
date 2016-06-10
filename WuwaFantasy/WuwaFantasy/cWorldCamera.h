#pragma once
#include "cCamera.h"
class cWorldCamera :
	public cCamera
{
private:
	float			m_fSpeed=3.0f;
public:
	cWorldCamera();
	virtual ~cWorldCamera();

	virtual void Update();
};

