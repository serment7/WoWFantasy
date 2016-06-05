
#include "stdafx.h"
#include "cGameObject.h"


cGameObject::cGameObject()
{

}

cGameObject::~cGameObject()
{
	SAFE_DELETE(m_chrSkinnedMesh);
}