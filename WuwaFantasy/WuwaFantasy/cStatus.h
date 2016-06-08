
#pragma once

struct ST_STATUS
{
	//포인트 정보
	int nCurrentHP = 0;
	int nMaxHP = 0;
	int nCurrentMP = 0;
	int nMaxMP = 0;
	int nCurrentSP = 0;
	int nMaxSP = 0;
	float fSpeed = 0.0f;

	//스테이터스 정보
	int nStr = 0;					//?E
	int nDex = 0;					//민첩성		
	int nDef = 0;					//방엉澹
	int nInt = 0;					//마력
	float fCrt = 0.0f;					//크리티컬

	int nLevel = 0;
	float fExp = 0.0f;
};

class cStatus
{
private:
	ST_STATUS m_stStatus;
	static int nLevelPoint;
public:
	cStatus();
	~cStatus();

	//스테이터스 셋팅부분
	void Setup(const ST_STATUS& stChInfo);

	//스테이터스 겟터 셋터(필요한 능력치 추가해 주세퓖E
	ST_STATUS GetStatus() { return m_stStatus; }

	int		GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int		GetMaxHP() { return m_stStatus.nMaxHP; }
	int		GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int		GetMaxMP() { return m_stStatus.nMaxMP; }
	int		GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int		GetMaxSP() { return m_stStatus.nMaxSP; }
	float	GetSpeed() const { return m_stStatus.fSpeed; }
	int		GetStr() { return m_stStatus.nStr; }					//?E
	int		GetDex() { return m_stStatus.nDex; }					//민첩성		
	int		GetDef() { return m_stStatus.nDef; }					//방엉澹
	int		GetInt() { return m_stStatus.nInt; }					//마력
	float	GetCrt() { return m_stStatus.fCrt; }					//크리티컬
	int		GetLevel() { return m_stStatus.nLevel; }
	float	GetExp() { return m_stStatus.fExp; }

	void	SetCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP = nCurrentHP; }
	void	SetMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP = nMaxHP; }
	void	SetCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP = nCurrentMP; }
	void	SetMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP = nMaxMP; }
	void	SetCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP = nCurrentSP; }
	void	SetMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP = nMaxSP; }
	void	SetSpeed(const float& fSpeed) { m_stStatus.fSpeed = fSpeed; }
	void	SetStr(const int& nStr) { m_stStatus.nStr = nStr; }					//?E
	void	SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//민첩성		
	void	SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//방엉澹
	void	SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//마력
	void	SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//크리티컬
	void	SetLevel(const int& nLevel) { m_stStatus.nLevel = nLevel; }
	void	SetExp(const float& fExp) { m_stStatus.fExp = fExp; }

	void	IncCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP += nCurrentHP; }
	void	IncMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP += nMaxHP; }
	void	IncCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP += nCurrentMP; }
	void	IncMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP += nMaxMP; }
	void	IncCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP += nCurrentSP; }
	void	IncMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP += nMaxSP; }
	void	IncSpeed(const float& fSpeed) { m_stStatus.fSpeed += fSpeed; }
	void	IncStr(const int& nStr) { m_stStatus.nStr += nStr; }					//?E
	void	IncDex(const int& nDex) { m_stStatus.nDex += nDex; }					//민첩성		
	void	IncDef(const int& nDef) { m_stStatus.nDef += nDef; }					//방엉澹
	void	IncInt(const int& nInt) { m_stStatus.nInt += nInt; }					//마력
	void	IncCrt(const float& fCrt) { m_stStatus.fCrt += fCrt; }					//크리티컬
	void	IncLevel(const int& nLevel) { m_stStatus.nLevel += nLevel; }
	void	IncExp(const float& fExp) { m_stStatus.fExp += fExp; }

	void	DecCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP -= nCurrentHP; }
	void	DecMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP -= nMaxHP; }
	void	DecCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP -= nCurrentMP; }
	void	DecMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP -= nMaxMP; }
	void	DecCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP -= nCurrentSP; }
	void	DecMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP -= nMaxSP; }
	void	DecSpeed(const float& fSpeed) { m_stStatus.fSpeed -= fSpeed; }
	void	DecStr(const int& nStr) { m_stStatus.nStr -= nStr; }					//?E
	void	DecDex(const int& nDex) { m_stStatus.nDex -= nDex; }					//민첩성		
	void	DecDef(const int& nDef) { m_stStatus.nDef -= nDef; }					//방엉澹
	void	DecInt(const int& nInt) { m_stStatus.nInt -= nInt; }					//마력
	void	DecCrt(const float& fCrt) { m_stStatus.fCrt -= fCrt; }					//크리티컬
	void	DecLevel(const int& nLevel) { m_stStatus.nLevel -= nLevel; }
	void	DecExp(const float& fExp) { m_stStatus.fExp -= fExp; }
};