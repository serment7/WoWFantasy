#pragma once

class cParsing;
const TCHAR SCRIPT_PATH[] = "Script/";

class cIScript
{
private:
	bool		m_bRun = false;

public:
	cIScript();
	~cIScript();

	bool IsRun();
	void RunScript();
	void StopScript();
	virtual void Update() = 0;
};
