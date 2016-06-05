
#pragma once
#include "cObject.h"
#include "cStatus.h"
#include "cSkinnedMesh.h"
#include "cWeaponSkinnedMesh.h"


class cGameObject : public cObject
{
public:
	cStatus*					m_pStatus;
	BOOL						m_isObject;

	cSkinnedMesh*				m_chrSkinnedMesh;
	cWeaponSkinnedMesh*			m_objSkinnedMesh;

public:
	cGameObject();
	virtual ~cGameObject();

};