#include "stdafx.h"
#include "cPoisonKnife.h"
#include "cGameObject.h"
#include "cPoison.h"

cPoisonKnife::cPoisonKnife(cGameObject * _pOwner, const float & _distance, const float & _attackTiming, const float & _fAniTime, cGameObject * _pThrown)
{
	SetPath("./Resource/UI/ºñ¼ö");
	SetOwner(_pOwner);
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(_distance);
	SetCoolDownTime(8.0f);

	m_fAttackTiming = _attackTiming;
	m_fAniTime = _fAniTime;

	if (_pThrown)
	{
		m_pThrown = _pThrown;
		m_pThrown->GetAction()->SetDelegate(this);
		m_pThrown->GetStatus().SetSpeed(7.0f);
		m_pThrown->SetUseAngle(true);
		m_pThrown->SetCalcHeight(false);
	}
	m_nNecessaryMP = 10;
}

cPoisonKnife::~cPoisonKnife()
{
	SAFE_RELEASE(m_pThrown);
}

void cPoisonKnife::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_bAttack = false;
	SetCast(true);
	m_fPassedTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	SetCoolDown(true);
	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_ThrowAni, NULL);
	SetEffectValue(m_pOwnerStatus->GetAttackDamage() * 2);
	m_fAngleY = 0.0f;
}

void cPoisonKnife::Update(const float & _delta)
{
	if (m_bAttack)
	{
		m_fAngleY += _delta*4.0f;
		m_pThrown->GetAction()->MoveTo();
		m_pThrown->SetRotation(m_fAngleY*D3DX_PI, 'y');
		m_pThrown->Update();
	}

	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedTime = 0.0f;
		m_bAttack = false;
	}

	if (IsCast() && GetTarget())
	{
		m_fPassedTime += _delta;
		if (m_fPassedTime > m_fAniTime)
		{
			SetCast(false);
			g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
		}
		if (!m_bAttack)
		{
			if (m_fPassedTime > m_fAttackTiming)
			{
				if (m_pThrown)
				{
					g_pSoundManager->Start("Throw");
					m_pThrown->SetVPos(GetOwner()->GetBoundSphere().vCenter+D3DXVECTOR3(0, 0.5f,0));
					m_pThrown->GetAction()->ReadyMoveTo(GetTarget()->GetVPos() + D3DXVECTOR3(0, 0.5f, 0));
					m_pThrown->GetAction()->Start();
					m_bAttack = true;
				}
				else
					SetCast(false);
			}
		}
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
			SetCoolDown(false);
	}
}

void cPoisonKnife::Render()
{
	if (m_bAttack)
	{
		m_pThrown->Render();
	}
}

void cPoisonKnife::Stop()
{
	SetCast(false);
}

bool cPoisonKnife::CanUse()
{
	return cSkill::CanUse() && GetTarget();
}

void cPoisonKnife::OnActionDelegate(cAction * _pSender)
{
	m_bAttack = false;
	if (GetTarget())
	{
		size_t targetID = GetTarget()->GetID();
		packet_condition = new Packet_AddCondition(new cPoison(GetTarget(),m_pOwnerStatus->GetAttackDamage()*0.3f,1.0f,10.0f));
		g_pMessageDispatcher->Dispatch(m_ownerID, targetID, 0.0f, Msg_AddCondition, packet_condition);
		packet_condition = nullptr;
		m_pThrown->GetAction()->Stop();
	}
}
