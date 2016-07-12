#include "stdafx.h"
#include "cBlizzard.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cRecursiveParticle.h"
#include "cThrownObject.h"
#include "cRandom.h"
#include "cAction.h"

cBlizzard::cBlizzard(cGameObject* _pOwner,const float& _distance)
{
	SetDistance(_distance);
	SetOwner(_pOwner);
	m_pOwnerStatus = &_pOwner->GetStatus();
	m_ownerID = _pOwner->GetID();

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

	m_fCoolDownTime = 20.0f;

	SetSkillType(skilltype::continuous);
	m_skillRange.vCenter = D3DXVECTOR3(0, 0, 0);
	m_skillRange.fRadius = 2* _pOwner->GetVScale().x;

	m_pParticleEffect = new cParticleEffect;
	SetCanMove(true);
	m_pParticleEffect->SetSize(0.5f);

	cRandom::SRand();
	for (int i = 0; i < 50; ++i)
	{
		m_pParticleEffect->AddParticle(
			new cThrownObject(m_skillRange.fRadius, 3.0f, -3.0f, 1.5f, true, D3DCOLOR_XRGB(75, 75, 255)));
	}
	for (int i = 0; i < 15; ++i)
	{
		m_pParticleEffect->AddParticle(new cRecursiveParticle(m_skillRange.vCenter, m_skillRange.fRadius,
			3.0f, (float)i*(360 / 15.0f), m_fRunTime, D3DCOLOR_XRGB(75, 75, 255)));
	}
	for (int i = 0; i < 10; ++i)
	{
		m_pParticleEffect->AddParticle(new cRecursiveParticle(m_skillRange.vCenter, m_skillRange.fRadius - 0.5f,
			3.0f, (float)i*(360 / 10.0f), m_fRunTime, D3DCOLOR_XRGB(75, 75, 255)));
	}
}


cBlizzard::~cBlizzard()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cBlizzard::Start()
{
	if (!CanUse())
		return;
	m_fPassedTime = 0.0f;
	SetCast(true);
	SetCoolDown(true);
	m_fNextHitTime = 0.0f;
	m_fCoolDownPassedTime = 0.0f;
	g_pMessageDispatcher->Dispatch(m_ownerID, m_ownerID, 0.0f, Msg_AttackEnd, NULL);
}

void cBlizzard::Update(const float & _delta)
{
	SetEffectValue(m_pOwnerStatus->GetAttackDamage()*0.2f);
	m_skillRange.vCenter = GetOwner()->GetVPos();
	
	if (m_pOwnerStatus->GetCurrentHP() < 1)
	{
		SetCast(false);
		SetCoolDown(false);
		m_fCoolDownPassedTime = 0.0f;
		m_fPassedTime = 0.0f;
	}

	if (IsCast())
	{
		m_fPassedTime += _delta;
		if (m_fPassedTime < m_fRunTime)
		{
			m_vPos = m_skillRange.vCenter;
			D3DXMatrixTranslation(&m_matWorld,m_vPos.x,m_vPos.y,m_vPos.z);
			m_pParticleEffect->SetMatrix(m_matWorld);
			m_pParticleEffect->Update(_delta);
			if (m_fPassedTime > m_fNextHitTime)
			{
				for (size_t i = 0; i < m_vecTargetTag.size(); ++i)
				{
					const std::vector<cGameObject*> targets = g_pObjectManager->FindObjectByTag(m_vecTargetTag[i]);
					for (size_t j = 0; j < targets.size(); ++j)
					{
						D3DXVECTOR3	vCheckPos = targets[j]->GetVPos();
						D3DXVECTOR3	vRange;
						D3DXVec3Normalize(&vRange, &(m_vPos - vCheckPos));
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
				g_pSoundManager->Start("Blizzard");
			}
		}
		else
		{
			if (m_pDelegate)
				m_pDelegate->OnSkillDelegate(this);
			SetCast(false);
			SetCoolDown(true);
		}
	}
	else if(IsCoolDown())
	{
		m_fCoolDownPassedTime += _delta;
		if (m_fCoolDownPassedTime > m_fCoolDownTime)
		{
			SetCoolDown(false);
		}
	}
	
}

void cBlizzard::Render()
{
	if (IsCast())
	{
		m_pParticleEffect->Render();
	}
}

void cBlizzard::Stop()
{
}