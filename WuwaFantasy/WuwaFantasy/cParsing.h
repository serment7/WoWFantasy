#pragma once
class cParsing
{
private:
	FILE*	m_fp;
	char	m_szToken[1024];
	std::string ret;
	int		m_length;

public:
	cParsing();
	cParsing(const char* _path);
	cParsing(const std::string& _path);
	virtual ~cParsing();

	bool		Load(char* _path);
	const std::string&		GetToken();
	bool		IsWhite(const char& c);
	bool		IsFeof();
	bool		SkipTo(const char* _path);
	bool		SkipTo(const std::string& _path);
	const int	GetInteger();
	const float	GetFloat();
};