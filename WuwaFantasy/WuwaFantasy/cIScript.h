#pragma once
class cIScript
{
private:
	bool		m_bRun;
public:
	cIScript();
	~cIScript();

	bool IsRun();
	virtual void RunScript();
	virtual void StopScript();
};

