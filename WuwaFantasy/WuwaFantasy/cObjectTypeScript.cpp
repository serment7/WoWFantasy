#include "stdafx.h"
#include "cObjectTypeScript.h"
#include"cParsing.h"

const TCHAR SCRIPT_INIT_GAMEDATA[] = "ObjectType.txt";

cObjectTypeScript::cObjectTypeScript()
{
	m_pParser = new cParsing(SCRIPT_PATH + std::string(SCRIPT_INIT_GAMEDATA));
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
			m_strToken=m_pParser->GetToken();
			if (m_strToken=="index")
			{
				m_unObjectTypeIndex = m_pParser->GetInteger();
			}
		}
		while (!m_pParser->IsFeof())
		{
			if (m_pParser->SkipTo("type"))
			{
				m_strToken=m_pParser->GetToken();
				g_pGameManager->RegisterObjectType(m_strToken,
					m_unObjectTypeIndex++);
			}
		}
		StopScript();

	}
}
