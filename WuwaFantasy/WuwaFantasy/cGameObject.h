
#pragma once
#include "cObject.h"
#include "cStatus.h"
#include "cSkinnedMesh.h"
#include "cWeaponSkinnedMesh.h"

const TCHAR MODEL_PATH[] = "./Resource/Model";

class cGameObject : public cObject
{
public:
	cStatus						m_pStatus;
	BOOL						m_isObject;

	cSkinnedMesh*				m_chrSkinnedMesh;
	cWeaponSkinnedMesh*			m_objSkinnedMesh;

protected:
	cSkinnedMesh* GetSkinnedMesh() { return m_chrSkinnedMesh; };

public:
	cGameObject();
	virtual ~cGameObject();

	cStatus& GetStatus();
};