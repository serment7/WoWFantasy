#include "stdafx.h"
#include "cPlayerState.h"
#include "cGameObject.h"
#include "cGrid.h"
#include "cMap.h"
#include "cCamera.h"
#include "cSkill.h"
#include "cUITextView.h"

cPlayerState::cPlayerState(cIState* _state)
{
	m_pState = _state;
}

cPlayerState::~cPlayerState()
{
	SAFE_DELETE(m_pState);
	for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
	{
		SAFE_DELETE(iter->second);
	}
	m_mapSkill.clear();
}

void cPlayerState::EnterState(cGameObject * _entity)
{
	ZeroMemory(&m_packet, sizeof(m_packet));
	m_mapTag = g_pGameManager->FindObjectType("map");
	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	m_pStatus = &_entity->GetStatus();
	m_entityID = _entity->GetID();
	_entity->SetName("³»¼Õ¾È¿¡Èæ¿°·æÀÌ");
	
	m_pState->EnterState(_entity);
	cEntityState::EnterState(_entity);
	m_pNameText->SetTextColor(D3DCOLOR_XRGB(0, 255, 0));

	m_vecPartyNPC=g_pObjectManager->FindObjectByTag(g_pGameManager->FindObjectType("combatnpc"));
	std::vector<size_t> partylist;
	partylist.push_back(m_entityID);
	for (size_t i = 0; i < m_vecPartyNPC.size(); ++i)
	{
		g_pUserHUD->AddParty(g_pObjectManager->FindObjectByID(m_vecPartyNPC[i]->GetID()));
		partylist.push_back(m_vecPartyNPC[i]->GetID());
	}
	
	for (size_t i = 0; i < partylist.size(); ++i)
	{
		for (size_t j = 0; j < partylist.size(); ++j)
		{
			g_pMessageDispatcher->Dispatch(partylist[i], partylist[j], 0.0f, Msg_JoinParty, NULL);
		}
	}
}

void cPlayerState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
	
}

void cPlayerState::Execute(cGameObject * _entity)
{
	cEntityState::Execute(_entity);

	m_pState->Execute(_entity);

	m_vCurPos = _entity->GetVPos();

	if (m_pTarget&&m_pTarget->GetStatus().GetCurrentHP() < 1)
	{
		for (size_t index = 0; index<m_vecPartyNPC.size(); ++index)
		{
			g_pMessageDispatcher->Dispatch(m_entityID, m_vecPartyNPC[index]->GetID(), 0.0f, Msg_LostTarget, NULL);
		}
		m_pTarget = nullptr;
	}

	if (g_pKeyManager->isOnceKeyDown(BASE_ATTACK))
	{
		m_mapSkill[BASE_ATTACK]->SetTarget(m_pTarget);
		if (m_mapSkill[BASE_ATTACK]->CanUse())
		{
			m_pCurSkill = m_mapSkill[BASE_ATTACK];
			if (m_pTarget)
			{
				m_bCombat = true;

			}
		}
	}

	if (m_bCombat && m_pTarget)
	{
		if (0 < m_pTarget->GetStatus().GetCurrentHP())
		{
			m_mapSkill[BASE_ATTACK]->SetTarget(m_pTarget);
			if (!m_pCurSkill && m_mapSkill[BASE_ATTACK]->CanUse())
			{
				m_pCurSkill = m_mapSkill[BASE_ATTACK];
			}
		}
		else
		{
			m_pTarget = nullptr;
			m_bCombat = false;
			g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
		}
	}

	if (m_pCurSkill && m_pCurSkill->CanUse())
	{
		if (m_pCurSkill->GetSKillType() != skilltype::Support)
		{
			packet_attack = new Packet_Attack(m_pTarget, m_pCurSkill);
			g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_Attack,packet_attack);
			for (size_t i = 0; i < m_vecPartyNPC.size(); ++i)
			{
				packet_target = new Packet_Target(m_pTarget);
				g_pMessageDispatcher->Dispatch(m_entityID, m_vecPartyNPC[i]->GetID(), 0.0f, Msg_Target, packet_target);
			}
		}
	}

	float delta = g_pTimeManager->GetDeltaTime();

	for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
	{
		iter->second->Update(delta);
	}

	int gridId = g_pGameManager->FindObjectType("collider");
	
	g_pGameManager->UpdateCursorPointInGlobal();
	const POINT& curPos = g_pGameManager->GetCursorPoint();

	D3DXVECTOR3 vDir=D3DXVECTOR3(0,0,0);
	D3DXMATRIXA16	matRotY;
	bool bMove= false;
	float speed = _entity->GetStatus().GetSpeed();
	float angle = g_pGameManager->GetCamera()->GetAngleY();
	D3DXVECTOR3 vLeft;
	D3DXVECTOR3 vRight;
	D3DXVECTOR3 vGo;
	D3DXVECTOR3 vBack;

	if (g_pKeyManager->isOnceKeyDown(VK_LBUTTON))
	{
		for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
		{
			std::vector<cGameObject*>& vecObject=g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
			for (size_t j = 0; j < vecObject.size(); ++j)
			{
				if (g_pPickManager->IsPickedSphere(vecObject[j]->GetBoundSphere(), curPos.x, curPos.y))
				{
					if (m_pTarget && 1 > m_pTarget->GetStatus().GetCurrentHP())
					{
					}
					if (!m_pTarget || 0 < vecObject[j]->GetStatus().GetCurrentHP())
					{
						m_pTarget = vecObject[j];
						g_pUserHUD->SetTarget(m_pTarget);
						break;
					}
					
				}
			}
		}
	}

	if (g_pKeyManager->isStayKeyDown('W'))
	{
		vDir += D3DXVECTOR3(0, 0, 1);
		bMove = true;
	}
	if (g_pKeyManager->isStayKeyDown('S'))
	{
		vDir += D3DXVECTOR3(0, 0, -1);
		bMove = true;
	}
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		vDir += D3DXVECTOR3(-1, 0, 0);
		bMove = true;
	}
	if (g_pKeyManager->isStayKeyDown('D'))
	{
		vDir += D3DXVECTOR3(1, 0, 0);
		bMove = true;
	}
	if (!m_bLive)
		return;
	if (bMove)
	{
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(angle));
		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);
		D3DXVec3Normalize(&vDir,&vDir);
		_entity->SetVDir(vDir);
		//_entity->SetVPos(_entity->GetVPos() + vDir*speed*0.03f);
		packet_move = new Packet_Pos(m_vCurPos + vDir);
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Move, packet_move);

		//m_packet.msg_type = Msg_MoveAni;
		//m_pState->OnMessage(_entity, m_packet);
		//g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Standby, NULL);
		m_bCombat = false;
		if(m_pCurSkill)
			m_pCurSkill->Stop();
	}
	else if (m_bCombat)
	{
		
	}
	else
	{
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_Idle, NULL);
	}	
}

bool cPlayerState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_UseSkill:
		packet_useskill = (Packet_UseSkill*)_packet.info;
		m_mapSkill[packet_useskill->key]->SetTarget(m_pTarget);
		if (m_mapSkill[packet_useskill->key]->CanUse())
		{
			m_pCurSkill = m_mapSkill[packet_useskill->key];
			m_bCombat = true;
		}
		SAFE_DELETE(packet_useskill);
		return true;
	case Msg_AttackEnd:
		g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f,Msg_Idle,NULL);
		m_pCurSkill = nullptr;
		return true;
	case Msg_AddCondition:
		packet_condition = (Packet_AddCondition*)_packet.info;
		_entity->AddCondition(packet_condition->pCondition);
		SAFE_DELETE(packet_condition);
		return true;
	case Msg_Render:
		m_pUIRoot->Render(g_pSpriteManager->GetSprite());
		if (m_bLive)
		{
			for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
			{
				iter->second->Render();
			}
		}
		return true;
	case Msg_JoinParty:
		m_vecPartyNPC.push_back(g_pObjectManager->FindObjectByID(_packet.sender));
		return true;
	case Msg_Hit:
		packet_hit = (Packet_Hit*)_packet.info;
		g_pSoundManager->Start("hit");
		m_pStatus->DecCurrentHP(packet_hit->damage - m_pStatus->GetDef());
		if (0 < m_pStatus->GetCurrentHP())
		{
			for (size_t index = 0; index < m_vecPartyNPC.size(); ++index)
			{
				g_pMessageDispatcher->Dispatch(m_entityID, m_vecPartyNPC[index]->GetID(), 0.0f, Msg_NeedHeal, NULL);
			}
		}
		else
		{
			m_bCombat = false;
			m_pTarget = nullptr;
			m_pStatus->SetCurrentHP(m_pStatus->GetMaxHP());
			m_pStatus->SetCurrentMP(m_pStatus->GetMaxMP());
			D3DXVECTOR3	vRespawn = g_pGameManager->GetRespawnPos();
			_entity->SetVPos(vRespawn);
			
			m_packet.msg_type = Msg_Respawn;
			m_pState->OnMessage(_entity,m_packet);
			for (size_t index = 0; index < m_vecPartyNPC.size(); ++index)
			{
				packet_move = new Packet_Pos(vRespawn);
				g_pMessageDispatcher->Dispatch(m_entityID,m_vecPartyNPC[index]->GetID(),0.0f,Msg_Respawn, packet_move);
			}
			g_pSoundManager->Stop("bossbattle");
		}
		SAFE_DELETE(packet_hit);
		return true;
	case Msg_SetSkill:
		packet_setskill = (Packet_SetSkill*)_packet.info;
		packet_setskill->skill->SetOwner(_entity);
		m_mapSkill.insert(std::pair<char, cSkill*>(packet_setskill->key,packet_setskill->skill));
		g_pUserHUD->SetSkill(packet_setskill->key,packet_setskill->skill);
		SAFE_DELETE(packet_setskill);
		return true;
	case Msg_Target:
		packet_target = (Packet_Target*)_packet.info;
		m_pTarget = packet_target->pTarget;
		SAFE_DELETE(packet_target);
		return true;
	default:
		return m_pState->OnMessage(_entity,_packet);
	}
	return false;
}
