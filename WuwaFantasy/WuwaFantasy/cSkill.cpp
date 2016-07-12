#include "stdafx.h"
#include "cSkill.h"
#include "cParticle.h"

cSkill::cSkill()
{
}


cSkill::~cSkill()
{
}

void cSkill::SetDelegate(cSklilDelegate * _pDelegate)
{
	m_pDelegate = _pDelegate;
}

void cSkill::SetPath(const std::string & _path)
{
	m_path = _path;
}

const std::string & cSkill::GetPath()
{
	return m_path;
}

void cSkill::SetSkillName(const std::string & _skillname)
{
	m_skillname = _skillname;
}

const std::string & cSkill::GetSkillName() const
{
	return m_skillname;
}

void cSkill::SetOwner(cGameObject * _pOwner)
{
	m_pOwner = _pOwner;
}

void cSkill::SetTarget(cGameObject * _pTarget)
{
	m_pTarget = _pTarget;
}

cGameObject * cSkill::GetOwner()
{
	return m_pOwner;
}

cGameObject * cSkill::GetTarget()
{
	return m_pTarget;
}

bool cSkill::IsCast()
{
	return m_bCast;
}

void cSkill::SetCast(const bool _bCast)
{
	m_bCast = _bCast;
}

void cSkill::SetEffectValue(const int & _effectValue)
{
	m_nEffectValue = _effectValue;
}

const int & cSkill::GetEffectValue()
{
	return m_nEffectValue;
}

void cSkill::SetSkillType(const skilltype & _type)
{
	m_skilltype = _type;
}

const skilltype & cSkill::GetSKillType()
{
	return m_skilltype;
}

const float & cSkill::GetPassedCoolTime()
{
	return m_fCoolDownPassedTime;
}

void cSkill::SetCoolDownTime(const float & _fCoolDownTime)
{
	m_fCoolDownTime = _fCoolDownTime;
}

const float & cSkill::GetCoolDownTime()
{
	return m_fCoolDownTime;
}

void cSkill::InitSkill()
{
	m_bCoolDown = false;
	m_fCoolDownPassedTime = 0.0f;
	m_bCast = false;
	m_pTarget = nullptr;
}

void cSkill::SetCoolDown(const bool & _isCooldown)
{
	m_bCoolDown = _isCooldown;
}

bool cSkill::IsCoolDown()
{
	return m_bCoolDown;
}

bool cSkill::CanUse()
{
	if (m_bCoolDown || m_bCast)
		return false;
	else
		return true;
}

void cSkill::SetNecessaryHP(const int & _hp)
{
	m_nNecessaryHP = _hp;
}

const int & cSkill::GetNecessaryHP()
{
	return m_nNecessaryHP;
}

void cSkill::SetNecessaryMP(const int & _mp)
{
	m_nNecessaryMP = _mp;
}

const int & cSkill::GetNecessaryMP()
{
	return m_nNecessaryMP;
}

void cSkill::SetCanMove(const bool & _canmove)
{
	m_bCanMove = _canmove;
}

bool cSkill::CanMove()
{
	return m_bCanMove;
}

void cSkill::SetDistance(const float & _distance)
{
	m_fDistance = _distance;
}

const float & cSkill::GetDistance()
{
	return m_fDistance;
}
