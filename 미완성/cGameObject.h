
#pragma once
#include "cObject.h"
#include "cStatus.h"
#include "cSkinnedMesh.h"

class cGameObject : public cObject
{
private:
	cStatus*				m_Status;
	cSkinnedMesh*			m_SkinnedMesh;

public:
	cGameObject();
	~cGameObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();	


};