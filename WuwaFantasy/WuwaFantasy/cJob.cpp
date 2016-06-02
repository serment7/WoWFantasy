#include "stdafx.h"
#include "cJob.h"


cJob::cJob()
{
}

cJob::cJob(const std::string & _jobname)
{
	m_jobname = _jobname;
}

cJob::~cJob()
{
}

void cJob::SetName(const std::string & _jobname)
{
	m_jobname = _jobname;
}

const std::string & cJob::GetName() const
{
	return m_jobname;
}

void cJob::AddSkill(const std::string & _skillname)
{
	m_skill.push_back(_skillname);
}

const std::vector<std::string>& cJob::GetSkill()
{
	return m_skill;
}
