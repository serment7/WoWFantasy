#include "stdafx.h"
#include "cIScript.h"


cIScript::cIScript()
	: m_bRun(false)
{
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
