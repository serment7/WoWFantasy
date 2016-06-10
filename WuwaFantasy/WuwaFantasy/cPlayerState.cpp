#include "stdafx.h"
#include "cPlayerState.h"
#include "cGameObject.h"
#include "cGrid.h"
#include "cMap.h"
#include "cCamera.h"

enum KeyEnum
{
	SKILL0 = '0'
	, SKILL1
	, SKILL2
	, SKILL3
	, SKILL4
	, SKILL5
	, SKILL6
	, SKILL7
	, SKILL8
	, END
};

cPlayerState::cPlayerState(cIState* _state)
	:m_pState(_state)
{
}

cPlayerState::~cPlayerState()
{
}

void cPlayerState::EnterState(cGameObject * _entity)
{
	m_vecSkill.resize(10);
	ZeroMemory(&m_packet, sizeof(m_packet));
	m_pState->EnterState(_entity);
	m_mapTag = g_pGameManager->FindObjectType("map");
	//m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
	m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	m_pStatus = &_entity->GetStatus();
}

void cPlayerState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
	
}

void cPlayerState::Execute(cGameObject * _entity)
{
	const int& curHP = m_pStatus->GetCurrentHP();
	if (0 < curHP)
	{
	}
	else
	{

	}

	m_pState->Execute(_entity);

	int gridId = g_pGameManager->FindObjectType("collider");
	
	g_pGameManager->UpdateCursorPointInGlobal();
	const POINT& curPos = g_pGameManager->GetCursorPoint();

	const int& playerID = _entity->GetID();

	if (!m_pTarget)
	{

	}

	//if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	//{
	//	g_pGameManager->UpdateCursorPointInGlobal();
	//	const POINT& curPos = g_pGameManager->GetCursorPoint();
	//	std::vector<cMap*>& map = g_pGameManager->GetMap();
	//	std::vector<cGameObject*> grid = g_pObjectManager->FindObjectByTag(gridId);

	//	cGrid* gridtarget = (cGrid*)grid[0];
	//	for (int i = 0; i < 1; ++i)
	//	{
	//		if (g_pPickManager->IsPickedTry(gridtarget->GetTriVertex(), curPos.x, curPos.y))
	//		{
	//			packet_move = new Packet_Move(g_pPickManager->GetRayPos());
	//			packet_move->vDes.y = 0.0f;
	//			g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Move, packet_move);
	//		}
	//	}

	//}

	D3DXVECTOR3 vDir=D3DXVECTOR3(0,0,0);
	D3DXMATRIXA16	matRotY;
	bool bMove=false;
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
					m_pTarget = vecObject[j];
					break;
				}
			}
		}
		/*g_pGameManager->UpdateCursorPointInGlobal();
		const POINT& curPos = g_pGameManager->GetCursorPoint();

		for (int i = 0; i<g_pObjectManager->FindObjectByTag())
		if (g_pPickManager->IsPickedTry(m_pGrid->GetTriVertex(), curPos.x, curPos.y))
		{
		g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Target, packet_target);
		}*/
	}
	else if(g_pKeyManager->isOnceKeyDown(VK_RBUTTON))
	{
		if (m_pTarget)
		{
			for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
			{
				std::vector<cGameObject*>& vecObject = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
				for (size_t j = 0; j < vecObject.size(); ++j)
				{
					if (g_pPickManager->IsPickedSphere(vecObject[j]->GetBoundSphere(), curPos.x, curPos.y))
					{
						if (m_pTarget == vecObject[j])
						{
							g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Move, new Packet_Move(m_pTarget->GetVPos()));
							m_bCombat = true;
							break;
						}
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

	if (bMove)
	{
		D3DXMatrixRotationY(&matRotY, D3DXToRadian(angle));
		D3DXVec3TransformNormal(&vDir, &vDir, &matRotY);
		_entity->SetVDir(vDir);
		_entity->SetVPos(_entity->GetVPos() + vDir*speed*0.01f);
		m_packet.msg_type = Msg_MoveAni;
		m_pState->OnMessage(_entity, m_packet);
	}
	else
	{
		m_packet.msg_type=Msg_IdleAni;
		m_pState->OnMessage(_entity,m_packet);
	}

	for (int i = SKILL0; i < KeyEnum::END; ++i)
	{
		if (g_pKeyManager->isOnceKeyDown(i))
			g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_MoveAni, NULL);
	}
}

bool cPlayerState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	switch (_packet.msg_type)
	{
	case Msg_AttackTarget:
		if (m_pTarget)
		{
			
			m_packet.info = attack_packet;
			if (0 < m_pTarget->GetStatus().GetCurrentHP())
			{
				
			}
		}
		break;
	case Msg_Hit:
		packet_hit = (Packet_Hit*)_packet.info;
		m_pStatus->DecCurrentHP(packet_hit->damage);
		return true;
	case  Msg_Skill:
		packet_skill = (Packet_SkillKey*)_packet.info;
		if (0 <= packet_skill->skill &&
			packet_skill->skill < SKILL_MAXNUM)
		{
			m_packet.msg_type = Msg_CastingAni;
			m_pState->OnMessage(_entity,m_packet);
		}
		SAFE_DELETE(packet_skill);
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
