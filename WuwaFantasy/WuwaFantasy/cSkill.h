#pragma once
class cSkill
{
private:
	std::string			m_skillname;

public:
	cSkill();
	virtual ~cSkill();

	void				SetSkillName(const std::string& _skillname);
	const std::string&	GetSkillName() const;
	virtual void		Start() = 0;
	virtual void		Update() = 0;
};

