#include "stdafx.h"
#include "cMapModScript.h"
#include "cGameObject.h"
#include "cParsing.h"
#include "cHydraState.h"
#include "cScorpionState.h"
#include "cMonster.h"
#include "cKingOfLichState.h"
#include "cNamedMonster.h"

const TCHAR SCRIPT_INIT_GAMEDATA[] = "ModeScript.txt";

cMapModScript::cMapModScript(OUT std::vector<cGameObject*>& _vecObjects)
	:m_vecObjects(_vecObjects)
{
	m_pParser = new cParsing(SCRIPT_PATH + std::string(SCRIPT_INIT_GAMEDATA));
	ZeroMemory(&m_status,sizeof(m_status));
	m_status.nMaxHP = 10;
	m_status.nCurrentHP = 10;
	m_status.fchaseRange = 10.0f;
	m_status.fSenseRange = 10.0f;
	m_status.nAttackDamage = 10.0f;
}

cMapModScript::~cMapModScript()
{
	SAFE_DELETE(m_pParser);
}

void cMapModScript::Update()
{
	if (IsRun())
	{
		if (m_pParser->SkipTo("start"))
		{
			while (!m_pParser->IsFeof() && m_strToken!="end")
			{
				if (m_pParser->SkipTo("add"))
				{
					if (m_pParser->GetToken() == "GameObject")
					{
						if (m_pParser->SkipTo("name")); {
							m_objectName = m_pParser->GetToken();
						}

						if(m_pParser->SkipTo("type"))
							m_typeID = g_pGameManager->FindObjectType(m_pParser->GetToken());

						if (m_typeID == g_pGameManager->FindObjectType("player"))
						{
							if (m_pParser->SkipTo("position"))
							{
								m_vPos.x = m_pParser->GetFloat();
								m_vPos.y = 0;
								m_vPos.z = m_pParser->GetFloat();
								g_pGameManager->SetRespawnPos(m_vPos);
								g_pObjectManager->FindObjectByID(g_pGameManager->GetPlayerID())->SetVPos(m_vPos);
							}
						}
						else if (m_typeID == g_pGameManager->FindObjectType("monster"))
						{
							m_status = g_pGameManager->FindStatus(m_objectName);
							if (m_pParser->SkipTo("scale"))
							{
								m_vScale.x = m_pParser->GetFloat();
								m_vScale.y = m_pParser->GetFloat();
								m_vScale.z = m_pParser->GetFloat();
							}

							if (m_pParser->SkipTo("boundsphere"))
							{
								if (m_pParser->SkipTo("center"))
								{
									m_boundsphere.vCenter.x = m_pParser->GetFloat();
									m_boundsphere.vCenter.y = m_pParser->GetFloat();
									m_boundsphere.vCenter.z = m_pParser->GetFloat();
								}
								if (m_pParser->SkipTo("radius"))
								{
									m_boundsphere.fRadius = m_pParser->GetFloat();
								}
							}
							if (m_pParser->SkipTo("num"))
							{
								m_nNumObject = m_pParser->GetInteger();

								while (m_nNumObject)
								{
									if (m_pParser->SkipTo("position"))
									{
										m_vPos.x = m_pParser->GetFloat();
										m_vPos.y = 0;
										m_vPos.z = m_pParser->GetFloat();
										if (m_objectName == "Hydra")
										{
											m_pNewObject = new cMonster(m_objectName, m_vPos,new cHydraState, m_status);
										}
										else if (m_objectName=="Scolpion")
										{
											m_pNewObject = new cMonster(m_objectName, m_vPos, new cScorpionState, m_status);
										}
										else if (m_objectName == "KingOfLich")
										{
											m_pNewObject = new cNamedMonster(m_objectName, m_vPos, new cKingOfLichState, m_status);
										}
										else
										{
											m_pNewObject = nullptr;
										}

										if (m_pNewObject)
										{
											m_pNewObject->SetScaling(m_vScale.x, m_vScale.y, m_vScale.z);
											m_pNewObject->SetBoundSphere(m_boundsphere.fRadius, m_boundsphere.vCenter);
											m_vecObjects.push_back(m_pNewObject);
											m_pNewObject = nullptr;
										}
										--m_nNumObject;
									}
								}
							}
						}
					}
				}
			}
		}
		StopScript();
	}
}
