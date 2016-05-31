
#pragma once
#include "cObject.h"
#include "cStatus.h"

class cGameObject : public cObject
{
private:
	cStatus m_ChrStatus;

public:
	cGameObject();
	~cGameObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();

};