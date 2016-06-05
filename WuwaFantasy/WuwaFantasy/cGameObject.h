
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

	cSkinnedMesh*				m_chrSkinnedMesh = nullptr;
	cWeaponSkinnedMesh*			m_objSkinnedMesh = nullptr;

public:
	cGameObject();
	virtual ~cGameObject();

	cStatus& GetStatus();
	cSkinnedMesh* GetSkinnedMesh() { return m_chrSkinnedMesh; };
};