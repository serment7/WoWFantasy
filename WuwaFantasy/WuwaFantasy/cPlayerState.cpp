#include "stdafx.h"
#include "cPlayerState.h"
#include "cGameObject.h"
#include "cGrid.h"
#include "cMap.h"

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
}

void cPlayerState::ExitState(cGameObject * _entity)
{
	m_pState->ExitState(_entity);
	
}

void cPlayerState::Execute(cGameObject * _entity)
{
	m_pState->Execute(_entity);

	int gridId = g_pGameManager->FindObjectType("collider");
	

	const int& playerID = _entity->GetID();

	if (g_pKeyManager->isStayKeyDown(VK_RBUTTON))
	{
		g_pGameManager->UpdateCursorPointInGlobal();
		const POINT& curPos = g_pGameManager->GetCursorPoint();
		std::vector<cMap*>& map = g_pGameManager->GetMap();
		std::vector<cGameObject*> grid = g_pObjectManager->FindObjectByTag(gridId);

		cGrid* gridtarget = (cGrid*)grid[0];
		for (int i = 0; i < 1; ++i)
		{
			if (g_pPickManager->IsPickedTry(gridtarget->GetTriVertex(), curPos.x, curPos.y))
			{
				packet_move = new Packet_Move(g_pPickManager->GetRayPos());
				packet_move->vDes.y = 0.0f;
				g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Move, packet_move);
			}
		}

	}
	else if (g_pKeyManager->isStayKeyDown(VK_LBUTTON))
	{
		/*g_pGameManager->UpdateCursorPointInGlobal();
		const POINT& curPos = g_pGameManager->GetCursorPoint();

		for (int i = 0; i<g_pObjectManager->FindObjectByTag())
			if (g_pPickManager->IsPickedTry(m_pGrid->GetTriVertex(), curPos.x, curPos.y))
			{
				g_pMessageDispatcher->Dispatch(playerID, playerID, 0.0f, Msg_Target, packet_target);
			}*/
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
