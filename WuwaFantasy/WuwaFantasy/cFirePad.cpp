#include "stdafx.h"
#include "cFirePad.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cRecursiveParticle.h"
#include "cRandom.h"
#include "cParticle.h"

cFirePad::cFirePad(cGameObject * _pOwner, const float& _distance)
{
	SetPath("./Resource/UI/ºÒÀåÆÇ");

	m_nNecessaryMP = 10;

	SetOwner(_pOwner);
	m_pOwnerStatus = &_pOwner->GetStatus();
	SetTarget(_pOwner);
	m_ownerID = _pOwner->GetID();


	SetCast(false);
	SetCoolDown(false);

	m_fCoolDownTime = 15.0f;
	SetDistance(_distance);

	SetSkillType(skilltype::continuous);
	m_skillRange.vCenter = D3DXVECTOR3(0, _pOwner->GetBoundSphere().fRadius*0.5f, 0);
	m_skillRange.fRadius = 2.0f * _pOwner->GetVScale().x;

	size_t tagId = _pOwner->GetTag();
	if (tagId == g_pGameManager->FindObjectType("player"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	}
	else if (tagId == g_pGameManager->FindObjectType("combatnpc"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("monster"));
	}
	else if (tagId == g_pGameManager->FindObjectType("monster"))
	{
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("combatnpc"));
		m_vecTargetTag.push_back(g_pGameManager->FindObjectType("player"));
	}

	m_pParticleEffect = new cParticleEffect;
	SetCanMove(true);
	m_pParticleEffect->SetSize(2.0f);

	cRandom::SRand();
	cParticle* particle = new cParticle;
	particle->SetPos(D3DXVECTOR3(0, _pOwner->GetBoundSphere().fRadius*0.5f, 0));
	particle->SetColor(D3DCOLOR_XRGB(255, 0, 0));
	particle->SetLifeTime(10.0f);
	particle->SetLive(true);
	particle->SetRecycle(true);
	m_pParticleEffect->AddParticle(particle);
}

cFirePad::~cFirePad()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cFirePad::Start()
{
	if (!CanUse())
		return;

	if (m_nNecessaryMP > m_pOwnerStatus->GetCurrentMP())
		return;

	m_pOwnerStatus->DecCurrentMP(m_nNecessaryMP);

	m_fPassedTime = 0.0f;
	SetCast(true);
	SetCoolDown(true);
	m_fNextHitTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	SetEffectValue(GetOwner()->GetStatus().GetAttackDamage()*0.2f);
	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);

	m_skillRange.vCenter = GetOwner()->GetVPos();
	D3DXMatrixTranslation(&m_matWorld, m_skillRange.vCenter.x, m_skillRange.vCenter.y, m_skillRange.vCenter.z);
	m_pParticleEffect->SetMatrix(m_matWorld);

}

void cFirePad::Update(const float & _delta)
{
	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedTime = 0.0f;
	}

	m_skillRange.vCenter = GetOwner()->GetVPos();
	m_fPassedTime += _delta;

	if (IsCast())
	{
		if (m_fPassedTime < m_fRunTime)
		{
			D3DXMatrixTranslation(&m_matWorld, m_skillRange.vCenter.x, m_skillRange.vCenter.y, m_skillRange.vCenter.z);
			m_pParticleEffect->SetMatrix(m_matWorld);
			m_pParticleEffect->Update(_delta);
			if (m_fPassedTime > m_fNextHitTime)
			{
				for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
				{
					const std::vector<cGameObject*>& targets = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
					for (size_t j = 0; j < targets.size(); ++j)
					{
						D3DXVECTOR3	vCheckPos = targets[j]->GetVPos();
						D3DXVECTOR3	vRange;
						D3DXVec3Normalize(&vRange, &(GetOwner()->GetVPos() - vCheckPos));
						vRange *= targets[j]->GetBoundSphere().fRadius;
						vCheckPos += vRange;
						if (m_skillRange.IsPointIn(vCheckPos))
						{
							packet_hit = new Packet_Hit(GetEffectValue());
							g_pMessageDispatcher->Dispatch(m_ownerID, targets[j]->GetID(), 0.0f, Msg_Hit, packet_hit);
						}
					}
				}
				m_fNextHitTime += m_fPerHitTime;
				g_pSoundManager->Start("firepad");
			}
		}
		else
			SetCast(false);
	}

	if (IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
		{
			SetCoolDown(false);
		}
	}
}

void cFirePad::Render()
{
	if (IsCast())
	{
		m_pParticleEffect->Render();
	}
}

void cFirePad::Stop()
{
}
