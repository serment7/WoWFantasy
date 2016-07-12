#include "stdafx.h"
#include "cInitGameDataScript.h"
#include "cParsing.h"
#include "cPlayer.h"
#include "cCombatNPC.h"
#include "cGnomeHealerState.h"
#include "cHumanWarriorState.h"
#include "cElfRogueState.h"
#include "cDworfMageState.h"

const TCHAR SCRIPT_INIT_GAMEDATA[] = "InitGameData.txt";

cInitGameDataScript::cInitGameDataScript(OUT std::vector<cGameObject*>& _objects)
	:m_objects(_objects)
{
	m_pParser = new cParsing(SCRIPT_PATH + std::string(SCRIPT_INIT_GAMEDATA));
	ZeroMemory(&m_status, sizeof(m_status));
}


cInitGameDataScript::~cInitGameDataScript()
{
	SAFE_DELETE(m_pParser);
}

void cInitGameDataScript::Update()
{
	if (IsRun())
	{
		if (m_pParser->SkipTo("start"))
		{
			while (!m_pParser->IsFeof() && m_strToken!="end")
			{
				m_strToken = m_pParser->GetToken();
				if (m_strToken=="register")
				{
					m_strToken = m_pParser->GetToken();
					if (m_strToken == "status")
					{
						if (m_pParser->SkipTo("type"))
						{
							m_objectName = m_pParser->GetToken();
						}

						if (m_pParser->SkipTo("job"))
						{
							m_jobName = m_pParser->GetToken();
							if (m_jobName == "magician")
							{
								m_pState = new cDworfMageState;
							}
							else if (m_jobName == "rogue")
							{
								m_pState = new cElfLogState;
							}
							else if (m_jobName == "healer")
							{
								m_pState = new cGnomeHealerState;
							}
							else if (m_jobName == "warrior")
							{
								m_pState = new cHumanWarriorState;
							}
						}

						if (m_pParser->SkipTo("name"))
						{
							m_name = m_pParser->GetToken();
						}

						if (m_pParser->SkipTo("status"))
						{
							ProcessStatus();
						}

						if (m_objectName == "player")
						{
							m_pNewObject = new cPlayer(m_name, D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,1), m_pState,m_status);
							g_pGameManager->SetPlayerID(m_pNewObject->GetID());
						}
						else if (m_objectName == "combatnpc")
						{
							m_pNewObject = new cCombatNPC(m_name, D3DXVECTOR3(0,0,0), D3DXVECTOR3(0, 0, 1), m_pState, m_status);
						}
						else if(m_objectName=="monster")
						{
							g_pGameManager->RegisterStatus(m_name, m_status);
						}

						if (m_pNewObject)
						{
							m_objects.push_back(m_pNewObject);
							m_pNewObject->SetBoundSphere(m_boundsphere.fRadius,m_boundsphere.vCenter);
							m_pNewObject = nullptr;
						}
						
					}
				}
			}
		}
		StopScript();
	}
}

void cInitGameDataScript::ProcessStatus()
{
	ZeroMemory(&m_status,sizeof(m_status));
	if (m_pParser->SkipTo("{"))
	{
		while (m_strToken != "}")
		{
			m_strToken = m_pParser->GetToken();
			if (m_strToken == "curhp")
				m_status.nCurrentHP = m_pParser->GetInteger();
			else if (m_strToken == "maxhp")
				m_status.nMaxHP = m_pParser->GetInteger();
			else if (m_strToken == "curmp")
				m_status.nCurrentMP = m_pParser->GetInteger();
			else if (m_strToken == "maxmp")
				m_status.nMaxMP = m_pParser->GetInteger();
			else if (m_strToken == "cursp")
				m_status.nCurrentSP = m_pParser->GetInteger();
			else if (m_strToken == "maxsp")
				m_status.nMaxSP = m_pParser->GetInteger();
			else if (m_strToken == "speed")
				m_status.fSpeed = m_pParser->GetFloat();
			else if (m_strToken == "str")
				m_status.nStr = m_pParser->GetInteger();
			else if (m_strToken == "dex")
				m_status.nDex = m_pParser->GetInteger();
			else if (m_strToken == "def")
				m_status.nDef = m_pParser->GetInteger();
			else if (m_strToken == "int")
				m_status.nDef = m_pParser->GetInteger();
			else if (m_strToken == "crt")
				m_status.nDef = m_pParser->GetFloat();
			else if (m_strToken == "level")
				m_status.nDef = m_pParser->GetInteger();
			else if (m_strToken == "exp")
				m_status.nDef = m_pParser->GetFloat();
			else if (m_strToken == "chase")
				m_status.fchaseRange = m_pParser->GetFloat();
			else if (m_strToken == "sense")
				m_status.fSenseRange = m_pParser->GetFloat();
			else if (m_strToken == "attackdamage")
				m_status.nAttackDamage = m_pParser->GetInteger();
			else if (m_strToken == "boundsphere")
			{
				if (m_pParser->SkipTo("radius"))
					m_boundsphere.fRadius = m_pParser->GetFloat();
				if (m_pParser->SkipTo("center"))
				{
					m_boundsphere.vCenter.x = m_pParser->GetFloat();
					m_boundsphere.vCenter.y = m_pParser->GetFloat();
					m_boundsphere.vCenter.z = m_pParser->GetFloat();
				}
				m_pParser->SkipTo("}");
			}
				
		}
	}
}
