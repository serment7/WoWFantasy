#include "stdafx.h"
#include "cObjectTypeScript.h"
#include"cParsing.h"

const TCHAR SCRIPT_OBJECT_TYPE[] = "ObjectType.txt";

cObjectTypeScript::cObjectTypeScript()
{
	m_pParser = new cParsing(SCRIPT_PATH + std::string(SCRIPT_OBJECT_TYPE));
}

cObjectTypeScript::~cObjectTypeScript()
{
	SAFE_DELETE(m_pParser);
}

void cObjectTypeScript::Update()
{
	if (IsRun())
	{
		if (m_pParser->SkipTo("start"))
		{
			m_pToken=m_pParser->GetToken();
			if (m_pToken=="index")
			{
				m_unObjectTypeIndex = m_pParser->GetInteger();
			}
		}
		while (!m_pParser->IsFeof())
		{
			if (m_pParser->SkipTo("type"))
			{
				m_pToken=m_pParser->GetToken();
				g_pGameManager->RegisterObjectType(m_pToken,
					m_unObjectTypeIndex++);
			}
		}
		StopScript();

	}
}
