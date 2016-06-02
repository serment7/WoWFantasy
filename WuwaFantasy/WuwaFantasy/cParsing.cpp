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
	fopen_s(&m_fp, (_path).c_str(), "r");
	ZeroMemory(&m_szToken, sizeof(m_szToken));
}

cParsing::~cParsing()
{
}

bool cParsing::Load(char * _path)
{
	if (m_fp)
		return false;

	fopen_s(&m_fp, _path, "r");

	return true;
}

void cParsing::GetToken(OUT char * _out)
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

	if (_out && nReadCount == 0)
	{
		strcpy_s(_out, strlen("\0"),"\0");
	}
	
	m_szToken[nReadCount] = '\0';
	m_length = strlen(m_szToken);

	if(_out)
		strcpy_s(_out, m_length, m_szToken);
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
		GetToken(NULL);
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
	GetToken(NULL);
	return (int)atoi(m_szToken);
}

const float cParsing::GetFloat()
{
	GetToken(NULL);
	return (float)atof(m_szToken);
}