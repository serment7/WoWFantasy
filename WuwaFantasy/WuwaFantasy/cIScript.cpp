#include "stdafx.h"
#include "cIScript.h"
#include "cParsing.h"

cIScript::cIScript()
{
}

cIScript::cIScript(const std::string _scriptname)
{
	m_parser = new cParsing(_scriptname);
}

cIScript::cIScript(const char * _scriptname)
{
	m_parser = new cParsing(_scriptname);
}

cIScript::~cIScript()
{
}

bool cIScript::IsRun()
{
	return m_bRun;
}

void cIScript::RunScript()
{
	m_bRun = true;
}

void cIScript::StopScript()
{
	m_bRun = false;
}
