#include "stdafx.h"
#include "cIncDef.h"
#include "cParticleEffect.h"
#include "cThrownObject.h"
#include "cGameObject.h"

cIncDef::cIncDef(cGameObject* _pOwner, const int & _IncDefence, const float & _skilltime)
	:m_nIncDefence(_IncDefence), m_fConditionTime(_skilltime)
{
	SetOwner(_pOwner);
	m_pStatus = &_pOwner->GetStatus();
	m_pStatus->IncDef(_IncDefence);
	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(0.1f);


	m_skillRange.vCenter = D3DXVECTOR3(0, 0, 0);
	m_skillRange.fRadius = 0.3f;

	for (int i = 0; i < 50; ++i)
	{
		m_pParticleEffect->AddParticle(
			new cThrownObject(m_skillRange.fRadius, 3.0f, -3.0f, 1.5f, true, D3DCOLOR_XRGB(75, 75, 255)));
	}
}

cIncDef::~cIncDef()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cIncDef::Update(const float & _delta, bool & _lifeTime)
{
	m_fPassedTime += _delta;

	if (m_fPassedTime > m_fConditionTime)
	{
		m_pStatus->DecDef(m_nIncDefence);
		_lifeTime = true;
	}
	else
	{
		m_vPos = GetOwner()->GetVPos();
		D3DXMatrixTranslation(&m_matWorld, m_vPos.x, m_vPos.y, m_vPos.z);
		m_pParticleEffect->SetMatrix(m_matWorld);
		m_pParticleEffect->Update(_delta);
		_lifeTime = false;
	}
}

void cIncDef::Render()
{
	m_pParticleEffect->Render();
}
