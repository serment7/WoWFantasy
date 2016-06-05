#include "stdafx.h"
#include "cParsing.h"


cParsing::cParsing()
	: m_fp(NULL)
	, m_length(0)
{
	ZeroMemory(&m_szToken, sizeof(m_szToken));
}

cParsing::cParsing(const char * _path)
	: m_length(0)
{
	cParsing(std::string(_path));
}

cParsing::cParsing(const std::string & _path)
{
	fopen_s(&m_fp, (_path).c_str(), "rt");
	//fopen_s(&m_fp, "Script/ObjectType.txt", "rt");
	ZeroMemory(&m_szToken, sizeof(m_szToken));
}

cParsing::~cParsing()
{
	fclose(m_fp);
}

bool cParsing::Load(char * _path)
{
	if (m_fp)
		return false;

	fopen_s(&m_fp, _path, "r");

	return true;
}

const std::string& cParsing::GetToken()
{
	int nReadCount = 0;

	while (true)
	{
		char c = fgetc(m_fp);

		if (feof(m_fp)) break;

		if (IsWhite(c))
		{
			if (nReadCount == 0)
				continue;
			break;
		}
		m_szToken[nReadCount++] = c;
	}

	m_szToken[nReadCount] = '\0';
	m_length = strlen(m_szToken);
	ret = m_szToken;
	return ret;
}

bool cParsing::IsWhite(const char& c)
{
	return c < 33;
}

bool cParsing::IsFeof()
{
	return (feof(m_fp)) ? 1 : 0;
}

bool cParsing::SkipTo(const char * _path)
{
	while (true)
	{
		if (IsFeof())
			break;
		GetToken();
		if (!strcmp(m_szToken, _path))
			return true;
	}
	return false;
}

bool cParsing::SkipTo(const std::string & _path)
{
	return SkipTo(_path.c_str());
}

const int cParsing::GetInteger()
{
	GetToken();
	return (int)atoi(m_szToken);
}

const float cParsing::GetFloat()
{
	GetToken();
	return (float)atof(m_szToken);
}