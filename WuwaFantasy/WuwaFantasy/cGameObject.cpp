
#include "stdafx.h"
#include "cGameObject.h"


cGameObject::cGameObject()
{

}

cGameObject::~cGameObject()
{
	SAFE_DELETE(m_chrSkinnedMesh);
	SAFE_DELETE(m_objSkinnedMesh);
}

cStatus & cGameObject::GetStatus()
{
	return m_pStatus;
}
