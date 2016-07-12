#pragma once
#include "cIScript.h"
#include "cStatus.h"

class cGameObject;

class cMapModScript :
	public cIScript
{
private:
	cParsing*					m_pParser = nullptr;
	std::string					m_strToken;

	std::vector<cGameObject*>&	m_vecObjects;

	std::string					m_objectName;
	size_t						m_typeID=MAXSIZE_T;
	D3DXVECTOR3					m_vScale;
	D3DXVECTOR3					m_vPos;
	BoundingSphere				m_boundsphere;

	int							m_nNumObject;
	cGameObject*				m_pNewObject = nullptr;
	ST_STATUS					m_status;

public:
	cMapModScript(OUT std::vector<cGameObject*>& _vecObjects);
	virtual ~cMapModScript();

	virtual void Update();
};

