#include "stdafx.h"
#include "cDworfMageState.h"
#include "cGameObject.h"
#include "cBaseShortAttack.h"
#include "cFirePad.h"
#include "cFireHand.h"

cDworfMageState::cDworfMageState()
{
}

cDworfMageState::~cDworfMageState()
{
}

void cDworfMageState::EnterState(cGameObject * _entity)
{
	_entity->GetChrSkinnedMesh()->SetFolderName(MODEL_PATH + "DworfBattleMage");
	_entity->GetChrSkinnedMesh()->Load("DworfBattleMage.X");
	_entity->GetObjSkinnedMesh()->Load(std::string(MODEL_PATH + "hand/left").c_str(), "lefthand.X", _entity->GetChrSkinnedMesh(), "RThumb");

	m_entityID = _entity->GetID();

	m_pOwner = _entity;

	m_pAniController = _entity->GetChrSkinnedMesh()->GetAnimationController();
	m_chrmesh = _entity->GetChrSkinnedMesh();

	float fAttackPeriod = m_chrmesh->GetAnimationPeriod(13);
	packet_setskill = new Packet_SetSkill(VK_RBUTTON, new cBaseShortAttack(_entity,1.0f, fAttackPeriod*0.5f, fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL1, new cFirePad(_entity,FLT_MAX));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	packet_setskill = new Packet_SetSkill(KeyEnum::SKILL2, new cFireHand(_entity, 1.0f,fAttackPeriod*0.7f,fAttackPeriod));
	g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_SetSkill, packet_setskill);

	SetupAnimation(20);

	
}

void cDworfMageState::ExitState(cGameObject * _entity)
{
}

void cDworfMageState::Execute(cGameObject * _entity)
{
	m_pAniController->GetTrackDesc(0, &m_desc);
	m_fPassedAnitime += g_pTimeManager->GetDeltaTime();

	float f = m_fPassedAnitime / m_fCurPeriod;
	if (!m_bLive)
	{
		if (m_fPassedAnitime > m_fPeriod - 0.1f)
		{
			m_pAniController->SetTrackPosition(0, m_fPeriod - 0.1f);
		}
	}
	else if (m_bAttack)
	{
		if (m_fPassedAnitime > m_fPeriod - 0.1f)
		{
			m_pAniController->SetTrackPosition(0, 0.0f);
			m_bAttack = false;
		}
	}
}

bool cDworfMageState::OnMessage(cGameObject * _entity, const ST_PACKET & _packet)
{
	//idle20,move34,attack13
	switch (_packet.msg_type)
	{
	case Msg_Respawn:
		m_bLive = true;
		m_bAttack = false;
		return true;
	case Msg_IdleAni:
		SetupAnimation(20);
		m_bAttack = false;
		return true;
	case Msg_MoveAni:
		SetupAnimation(34);
		m_bAttack = false;
		return true;
	case Msg_AttackAni:
		SetupAnimation(13);
		m_bAttack = true;
		m_fPassedAnitime = 0.0f;
		return true;
	case Msg_CastingAni:
		SetupAnimation(17);
		m_bAttack = false;
		return true;
	case Msg_StunAni:
		SetupAnimation(29);
		m_bAttack = false;
		return true;
	case Msg_Death:
		SetupAnimation(32);
		m_bAttack = false;
		m_bLive = false;
		m_fPassedAnitime = 0.0f;
		return true;
	}
	return false;
}