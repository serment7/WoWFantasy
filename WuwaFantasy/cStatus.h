
#pragma once

struct ST_STATUS
{
	//ﾆﾎﾆｮ ﾁ､ｺｸ
	int nCurrentHP;
	int nMaxHP;
	int nCurrentMP;
	int nMaxMP;
	int nCurrentSP;
	int nMaxSP;
	float fSpeed;

	//ｽｺﾅﾗﾀﾌﾅﾍｽｺ ﾁ､ｺｸ
	int nStr;					//ﾈ・
	int nDex;					//ｹﾎﾃｸｼｺ		
	int nDef;					//ｹ貔﨧ﾂ
	int nInt;					//ｸｶｷﾂ
	float fCrt;					//ﾅｩｸｮﾆｼﾄﾃ

	int nLevel;
	float fExp;
};

class cStatus 
{
private:
	ST_STATUS m_stStatus;
	static int nLevelPoint;
public:
	cStatus();
	~cStatus();

	//ｽｺﾅﾗﾀﾌﾅﾍｽｺ ｼﾂﾆﾃｺﾎｺﾐ
	void Setup(const ST_STATUS& stChInfo);

	//ｽｺﾅﾗﾀﾌﾅﾍｽｺ ｰﾙﾅﾍ ｼﾂﾅﾍ(ﾇﾊｿ萇ﾑ ｴﾉｷﾂﾄ｡ ﾃﾟｰ｡ﾇﾘ ﾁﾖｼｼｿ・
	ST_STATUS GetStatus() { return m_stStatus; }

	int		GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int		GetMaxHP() { return m_stStatus.nMaxHP; }
	int		GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int		GetMaxMP() { return m_stStatus.nMaxMP; }
	int		GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int		GetMaxSP() { return m_stStatus.nMaxSP; }
	float	GetSpeed() { return m_stStatus.fSpeed; }
	int		GetStr() { return m_stStatus.nStr; }					//ﾈ・
	int		GetDex() { return m_stStatus.nDex; }					//ｹﾎﾃｸｼｺ		
	int		GetDef() { return m_stStatus.nDef; }					//ｹ貔﨧ﾂ
	int		GetInt() { return m_stStatus.nInt; }					//ｸｶｷﾂ
	float	GetCrt() { return m_stStatus.fCrt; }					//ﾅｩｸｮﾆｼﾄﾃ
	int		GetLevel() { return m_stStatus.nLevel; }
	float	GetExp() { return m_stStatus.fExp; }

	void	SetCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP = nCurrentHP; }
	void	SetMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP = nMaxHP; }
	void	SetCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP = nCurrentMP; }
	void	SetMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP = nMaxMP; }
	void	SetCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP = nCurrentSP; }
	void	SetMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP = nMaxSP; }
	void	SetSpeed(const float& fSpeed) { m_stStatus.fSpeed = fSpeed; }
	void	SetStr(const int& nStr) { m_stStatus.nStr = nStr; }					//ﾈ・
	void	SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//ｹﾎﾃｸｼｺ		
	void	SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//ｹ貔﨧ﾂ
	void	SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//ｸｶｷﾂ
	void	SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//ﾅｩｸｮﾆｼﾄﾃ
	void	SetLevel(const int& nLevel) { m_stStatus.nLevel = nLevel; }
	void	SetExp(const float& fExp) { m_stStatus.fExp = fExp; }
};