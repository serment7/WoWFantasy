#include "stdafx.h"
#include "cIncATK.h"
#include "cParticleEffect.h"
#include "cThrownObject.h"
#include "cGameObject.h"

cIncATK::cIncATK(cGameObject* _pOwner, const int& _IncAttackDamage, const float& _skilltime)
	:m_nIncAttackDamage(_IncAttackDamage), m_fConditionTime(_skilltime)
{
	SetOwner(_pOwner);
	m_pOwnerStatus=&_pOwner->GetStatus();
	m_pOwnerStatus->IncAttackDamage(_IncAttackDamage);
	m_pParticleEffect = new cParticleEffect;
	m_pParticleEffect->SetSize(0.1f);

	m_skillRange.vCenter = D3DXVECTOR3(0, 0, 0);
	m_skillRange.fRadius = 0.3;

	for (int i = 0; i < 50; ++i)
	{
		m_pParticleEffect->AddParticle(
			new cThrownObject(m_skillRange.fRadius, 3.0f, -3.0f, 1.5f, true, D3DCOLOR_XRGB(255, 75, 75)));
	}

}

cIncATK::~cIncATK()
{
	SAFE_DELETE(m_pParticleEffect);
}

void cIncATK::Update(const float & _delta, bool & _lifeTime)
{
	m_fPassedTime += _delta;
	
	

	if (m_fPassedTime > m_fConditionTime)
	{
		m_pOwnerStatus->DecAttackDamage(m_nIncAttackDamage);
		_lifeTime = true;
	}
	else
	{
		m_vPos = GetOwner()->GetVPos();
		D3DXMatrixTranslation(&m_matWorld,m_vPos.x,m_vPos.y,m_vPos.z);
		m_pParticleEffect->SetMatrix(m_matWorld);
		m_pParticleEffect->Update(_delta);
		_lifeTime = false;
	}
		
}

void cIncATK::Render()
{
	m_pParticleEffect->Render();
}
