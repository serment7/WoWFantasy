#include "stdafx.h"
#include "cExplosionKnife.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cBombParticle.h"

cExplosionKnife::cExplosionKnife(cGameObject * _pOwner, const float & _distance, const float & _attackTiming, const float & _fAniTime, cGameObject * _pThrown)
{
	SetPath("./Resource/UI/ÆøÅº");
	SetOwner(_pOwner);
	m_ownerID = _pOwner->GetID();
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetDistance(_distance);
	SetCoolDownTime(8.0f);
	m_pParticleEffect = new cParticleEffect;

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

	m_nNecessaryMP = 8;
}

cExplosionKnife::~cExplosionKnife()
{
	SAFE_RELEASE(m_pThrown);
	SAFE_DELETE(m_pParticleEffect);
}

void cExplosionKnife::Start()
{
	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_bAttack = false;
	SetCast(true);
	m_fPassedTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	SetCoolDown(true);
	g_pMessageDispatcher->Dispatch(m_ownerID,m_ownerID,0.0f,Msg_ThrowAni,NULL);
	SetEffectValue(m_pOwnerStatus->GetAttackDamage()*2);
	m_fAngleY = 0.0f;
}

void cExplosionKnife::Update(const float & _delta)
{
	if (m_bAttack)
	{
		m_fAngleY += _delta*4.0f;
		m_pThrown->GetAction()->MoveTo();
		m_pThrown->SetRotation(m_fAngleY*D3DX_PI, 'y');
		m_pThrown->Update();
	}
	m_pParticleEffect->Update(_delta);

	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedTime = 0.0f;
		m_bAttack = false;
	}

	if (IsCast()&&GetTarget())
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
					m_pThrown->SetVPos(GetOwner()->GetVPos()+D3DXVECTOR3(0, 0.5f, 0));
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

void cExplosionKnife::Render()
{
	if (m_bAttack)
	{
		m_pThrown->Render();
	}	
	m_pParticleEffect->Render();
}

void cExplosionKnife::Stop()
{
	SetCast(false);
}

bool cExplosionKnife::CanUse()
{
	return cSkill::CanUse()&&GetTarget();
}

void cExplosionKnife::OnActionDelegate(cAction * _pSender)
{
	m_bAttack = false;
	if (GetTarget())
	{
		size_t targetID = GetTarget()->GetID();
		m_pParticleEffect->AddParticle(
			new cBombParticle(m_pThrown->GetVPos(), m_pParticleEffect, 0.0f, 5.0f, 0.3f, D3DCOLOR_XRGB(255, 255, 125)));
		packet_hit = new Packet_Hit(GetEffectValue());
		g_pMessageDispatcher->Dispatch(m_ownerID,targetID,0.0f,Msg_Hit,packet_hit);
		packet_hit = nullptr;
		m_pThrown->GetAction()->Stop();
	}
}
