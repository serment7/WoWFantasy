
#pragma once

struct ST_STATUS
{
	//Æ÷ÀÎÆ® Á¤º¸
	int nCurrentHP = 0;
	int nMaxHP = 0;
	int nCurrentMP = 0;
	int nMaxMP = 0;
	int nCurrentSP = 0;
	int nMaxSP = 0;
	float fSpeed = 0.0f;

	//½ºÅ×ÀÌÅÍ½º Á¤º¸
	int nStr = 0;					//?E
	int nDex = 0;					//¹ÎÃ¸¼º		
	int nDef = 0;					//¹æ¾ûÓÂ
	int nInt = 0;					//¸¶·Â
	float fCrt = 0.0f;					//Å©¸®Æ¼ÄÃ

	int nAttackDamage = 0;
	int nArmor = 0;

	int nLevel = 0;
	float fExp = 0.0f;

	float fSenseRange = 0.0f;
	float fchaseRange = 0.0f;

	float fRespawnTime = 0.0f;

	float fAttackRange = 0.0f;
};

class cStatus
{
private:
	ST_STATUS m_stStatus;
	static int nLevelPoint;
public:
	cStatus();
	~cStatus();

	//½ºÅ×ÀÌÅÍ½º ¼ÂÆÃºÎºÐ
	void Setup(const ST_STATUS& stChInfo);

	//½ºÅ×ÀÌÅÍ½º °ÙÅÍ ¼ÂÅÍ(ÇÊ¿äÇÑ ´É·ÂÄ¡ Ãß°¡ÇØ ÁÖ¼¼¿E
	ST_STATUS GetStatus() { return m_stStatus; }

	int		GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int		GetMaxHP() { return m_stStatus.nMaxHP; }
	int		GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int		GetMaxMP() { return m_stStatus.nMaxMP; }
	int		GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int		GetMaxSP() { return m_stStatus.nMaxSP; }
	float	GetSpeed() const { return m_stStatus.fSpeed; }
	int		GetStr() { return m_stStatus.nStr; }					//?E
	int		GetDex() { return m_stStatus.nDex; }					//¹ÎÃ¸¼º		
	int		GetDef() { return m_stStatus.nDef; }					//¹æ¾ûÓÂ
	int		GetInt() { return m_stStatus.nInt; }					//¸¶·Â
	float	GetCrt() { return m_stStatus.fCrt; }					//Å©¸®Æ¼ÄÃ
	int		GetLevel() { return m_stStatus.nLevel; }
	float	GetExp() { return m_stStatus.fExp; }
	float	GetSenseRange() { return m_stStatus.fSenseRange; }
	float	GetChaseRange() { return m_stStatus.fchaseRange; }
	float	GetRespawnTime() { return m_stStatus.fRespawnTime; }
	float	GetAttackRange() { return m_stStatus.fAttackRange; }
	int		GetAttackDamage() { return m_stStatus.nAttackDamage; }
	int		GetArmor() { return m_stStatus.nArmor; }

	void	SetCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP = nCurrentHP; }
	void	SetMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP = nMaxHP; }
	void	SetCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP = nCurrentMP; }
	void	SetMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP = nMaxMP; }
	void	SetCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP = nCurrentSP; }
	void	SetMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP = nMaxSP; }
	void	SetSpeed(const float& fSpeed) { m_stStatus.fSpeed = fSpeed; }
	void	SetStr(const int& nStr) { m_stStatus.nStr = nStr; }					//?E
	void	SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//¹ÎÃ¸¼º		
	void	SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//¹æ¾ûÓÂ
	void	SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//¸¶·Â
	void	SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//Å©¸®Æ¼ÄÃ
	void	SetLevel(const int& nLevel) { m_stStatus.nLevel = nLevel; }
	void	SetExp(const float& fExp) { m_stStatus.fExp = fExp; }
	void	SetSenseRange(const float& _fSenseRange) { m_stStatus.fSenseRange = _fSenseRange; }
	void	SetChaseRange(const float& _fChaseRange) { m_stStatus.fchaseRange = _fChaseRange; }
	void	SetRespawnTime(const float& _fRespawnTime) { m_stStatus.fRespawnTime = _fRespawnTime; }
	void	SetAttackRange(const float& _fAttackRange) { m_stStatus.fAttackRange = _fAttackRange; }
	void	SetAttackDamage(const int& _nAttackDamage) { m_stStatus.nAttackDamage = _nAttackDamage; }
	void	SetArmor(const int& _nArmor) { m_stStatus.nArmor = _nArmor; }

	void	IncCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP += nCurrentHP;
	if (m_stStatus.nCurrentHP > m_stStatus.nMaxHP)
		m_stStatus.nCurrentHP = m_stStatus.nMaxHP;
	}
	void	IncMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP += nMaxHP; }
	void	IncCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP += nCurrentMP;
	if (m_stStatus.nCurrentMP > m_stStatus.nMaxMP)
		m_stStatus.nCurrentMP = m_stStatus.nMaxMP;
	}
	void	IncMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP += nMaxMP; }
	void	IncCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP += nCurrentSP; }
	void	IncMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP += nMaxSP; }
	void	IncSpeed(const float& fSpeed) { m_stStatus.fSpeed += fSpeed; }
	void	IncStr(const int& nStr) { m_stStatus.nStr += nStr; }					//?E
	void	IncDex(const int& nDex) { m_stStatus.nDex += nDex; }					//¹ÎÃ¸¼º		
	void	IncDef(const int& nDef) { m_stStatus.nDef += nDef; }					//¹æ¾ûÓÂ
	void	IncInt(const int& nInt) { m_stStatus.nInt += nInt; }					//¸¶·Â
	void	IncCrt(const float& fCrt) { m_stStatus.fCrt += fCrt; }					//Å©¸®Æ¼ÄÃ
	void	IncLevel(const int& nLevel) { m_stStatus.nLevel += nLevel; }
	void	IncExp(const float& fExp) { m_stStatus.fExp += fExp; }
	void	IncSenseRange(const float& _fSenseRange) { m_stStatus.fSenseRange += _fSenseRange; }
	void	IncChaseRange(const float& _fChaseRange) { m_stStatus.fchaseRange += _fChaseRange; }
	void	IncRespawnTime(const float& _fRespawnTime) { m_stStatus.fRespawnTime += _fRespawnTime; }
	void	IncAttackRange(const float& _fAttackRange) { m_stStatus.fAttackRange += _fAttackRange; }
	void	IncAttackDamage(const int& _nAttackDamage) { m_stStatus.nAttackDamage += _nAttackDamage; }
	void	IncArmor(const int& _nArmor) { m_stStatus.nArmor += _nArmor; }

	void	DecCurrentHP(const int& nCurrentHP)
	{
		if (0 < nCurrentHP)
		{
			m_stStatus.nCurrentHP -= nCurrentHP;
			if (m_stStatus.nCurrentHP < 1)
				m_stStatus.nCurrentHP = 0;
		}
	}
	void	DecMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP -= nMaxHP; 
	if (m_stStatus.nMaxHP < 1)
		m_stStatus.nMaxHP = 0;
	}
	void	DecCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP -= nCurrentMP;
	if (m_stStatus.nCurrentMP < 1)
		m_stStatus.nCurrentMP = 0;
	}
	void	DecMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP -= nMaxMP;
	if (m_stStatus.nMaxMP < 1)
		m_stStatus.nMaxMP = 0;
	}
	void	DecCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP -= nCurrentSP; }
	void	DecMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP -= nMaxSP; }
	void	DecSpeed(const float& fSpeed) { m_stStatus.fSpeed -= fSpeed; }
	void	DecStr(const int& nStr) { m_stStatus.nStr -= nStr; }					//?E
	void	DecDex(const int& nDex) { m_stStatus.nDex -= nDex; }					//¹ÎÃ¸¼º		
	void	DecDef(const int& nDef) { m_stStatus.nDef -= nDef; }					//¹æ¾ûÓÂ
	void	DecInt(const int& nInt) { m_stStatus.nInt -= nInt; }					//¸¶·Â
	void	DecCrt(const float& fCrt) { m_stStatus.fCrt -= fCrt; }					//Å©¸®Æ¼ÄÃ
	void	DecLevel(const int& nLevel) { m_stStatus.nLevel -= nLevel; }
	void	DecExp(const float& fExp) { m_stStatus.fExp -= fExp; }
	void	DecSenseRange(const float& _fSenseRange) { m_stStatus.fSenseRange -= _fSenseRange; }
	void	DecChaseRange(const float& _fChaseRange) { m_stStatus.fchaseRange -= _fChaseRange; }
	void	DecRespawnTime(const float& _fRespawnTime) { m_stStatus.fRespawnTime -= _fRespawnTime; }
	void	DecAttackRange(const float& _fAttackRange) { m_stStatus.fAttackRange -= _fAttackRange; }
	void	DecAttackDamage(const int& _nAttackDamage) { m_stStatus.nAttackDamage -= _nAttackDamage; }
	void	DecArmor(const int& _nArmor) { m_stStatus.nArmor -= _nArmor; }
};