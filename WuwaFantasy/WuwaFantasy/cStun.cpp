#include "stdafx.h"
#include "cStun.h"
#include "cGameObject.h"
#include "cParticleEffect.h"
#include "cRecursiveParticle.h"

cStun::cStun(cGameObject* _pOwner, const float& _fStunTime)
{
	SetOwner(_pOwner);
	m_entityID = _pOwner->GetID();
	m_fStunTime = _fStunTime;
	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(0.3f);
	m_pParticleEffect->SetTexture("yammi_star.bmp");
	g_pMessageDispatcher->Dispatch(m_entityID,m_entityID,0.0f, Msg_Stun, NULL);
	for (size_t i = 0; i < 5; ++i)
	{
		m_pParticleEffect->AddParticle(new cRecursiveParticle(D3DXVECTOR3(0, _pOwner->GetBoundSphere().fRadius, 0), 0.5f, 2.0f, i*(360.0f/5), _fStunTime,D3DCOLOR_XRGB(255,255,255)));
	}
}


cStun::~cStun()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cStun::Update(const float & _delta, bool & _lifeTime)
{
	if (m_fPassedTime > m_fStunTime)
	{
		g_pMessageDispatcher->Dispatch(m_entityID, m_entityID, 0.0f, Msg_StunEnd, NULL);
		_lifeTime = true;
	}
	else
	{
		m_fPassedTime += _delta;
		D3DXVECTOR3 vPos = GetOwner()->GetVPos();
		D3DXMatrixTranslation(&m_trans, vPos.x, vPos.y, vPos.z);
		m_pParticleEffect->SetMatrix(m_trans);
		m_pParticleEffect->Update(_delta);
		_lifeTime = false;
	}
}

void cStun::PostRender()
{
	m_pParticleEffect->Render();
}