#include "stdafx.h"
#include "cSkill.h"


cSkill::cSkill()
{
}


cSkill::~cSkill()
{
}

void cSkill::SetSkillName(const std::string & _skillname)
{
	m_skillname = _skillname;
}

const std::string & cSkill::GetSkillName() const
{
	return m_skillname;
}
