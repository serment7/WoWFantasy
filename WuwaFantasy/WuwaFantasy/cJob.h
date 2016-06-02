#pragma once
class cJob
{
private:
	std::string			m_jobname;
	std::vector<std::string>	m_skill;

public:
	cJob();
	cJob(const std::string& _jobname);
	virtual ~cJob();

	void				SetName(const std::string& _jobname);
	const std::string&	GetName() const;

	void				AddSkill(const std::string& _skillname);
	const std::vector<std::string>& GetSkill();
};

