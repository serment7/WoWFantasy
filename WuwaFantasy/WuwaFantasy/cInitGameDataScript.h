#pragma once
#include "cIScript.h"
#include "cStatus.h"

class cGameObject;
class cIState;

class cInitGameDataScript :
	public cIScript
{
private:
	cParsing*					m_pParser = nullptr;
	std::string					m_strToken;

	std::vector<cGameObject*>&  m_objects;

	std::string					m_objectName;
	std::string					m_jobName;
	std::string					m_name;
	cIState*					m_pState = nullptr;
	ST_STATUS					m_status;
	cGameObject*				m_pNewObject = nullptr;
	BoundingSphere				m_boundsphere;

public:
	cInitGameDataScript(OUT std::vector<cGameObject*>& _objects);
	virtual ~cInitGameDataScript();

	virtual void Update();
	virtual void ProcessStatus();
};

