#pragma once

class cParsing;

const TCHAR SCRIPT_PATH[] = "Script/";

class cIScript
{
private:
	bool		m_bRun = false;
	cParsing*	m_parser = nullptr;

public:
	cIScript();
	cIScript(const std::string _scriptname);
	cIScript(const char* _scriptname);
	~cIScript();

	bool IsRun();
	void RunScript();
	void StopScript();
	virtual void Update() = 0;
};
