
#pragma once
#include "cObject.h"
#include "cStatus.h"

class cSkinnedMesh;

const TCHAR MODEL_PATH[] = "./Resource/Model";

class cGameObject : public cObject
{
private:
	cSkinnedMesh*			m_mesh = nullptr;
	cStatus					m_ChrStatus;

protected:
	cSkinnedMesh* GetSkinnedMesh() { return m_mesh; };

public:
	cGameObject();
	~cGameObject();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void Release();

	cStatus& GetStatus();
};