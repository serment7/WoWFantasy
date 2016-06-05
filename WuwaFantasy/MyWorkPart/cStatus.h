
#pragma once

struct ST_STATUS
{
	//포인트 정보
	int nCurrentHP;
	int nMaxHP;
	int nCurrentMP;
	int nMaxMP;
	int nCurrentSP;
	int nMaxSP;
	float fSpeed;

	//스테이터스 정보
	int nStr;					//힘
	int nDex;					//민첩성		
	int nDef;					//방어력
	int nInt;					//마력
	float fCrt;					//크리티컬

	int nLevel;
	float fExp;

	//오퍼레이터
	operator+= (const ST_STATUS& stChInfo)
	{
		nCurrentHP += stChInfo.nCurrentHP;
		nMaxHP += stChInfo.nMaxHP;
		nCurrentMP += stChInfo.nCurrentMP;
		nMaxMP += stChInfo.nMaxMP;
		nCurrentSP += stChInfo.nCurrentSP;
		nMaxSP += stChInfo.nMaxSP;
		fSpeed += stChInfo.fSpeed;

		//스테이터스 정보
		nStr += stChInfo.nStr;					//힘
		nDex += stChInfo.nDex;					//민첩성		
		nDef += stChInfo.nDef;					//방어력
		nInt += stChInfo.nInt;					//마력
		fCrt += stChInfo.fCrt;					//크리티컬
	}

	operator-= (const ST_STATUS& stChInfo)
	{
		nCurrentHP -= stChInfo.nCurrentHP;
		nMaxHP -= stChInfo.nMaxHP;
		nCurrentMP -= stChInfo.nCurrentMP;
		nMaxMP -= stChInfo.nMaxMP;
		nCurrentSP -= stChInfo.nCurrentSP;
		nMaxSP -= stChInfo.nMaxSP;
		fSpeed -= stChInfo.fSpeed;

		//스테이터스 정보
		nStr -= stChInfo.nStr;					//힘
		nDex -= stChInfo.nDex;					//민첩성		
		nDef -= stChInfo.nDef;					//방어력
		nInt -= stChInfo.nInt;					//마력
		fCrt -= stChInfo.fCrt;					//크리티컬
	}
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

	void FixingStatusUp(const ST_STATUS& stChInfo);
	void FixingStatusDown(const ST_STATUS& stChInfo);

	//스테이터스 겟터 셋터(필요한 능력치 추가해 주세요)
	ST_STATUS GetStatus() { return m_stStatus; }

	int GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int GetMaxHP() { return m_stStatus.nMaxHP; }
	int GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int GetMaxMP() { return m_stStatus.nMaxMP; }
	int GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int GetMaxSP() { return m_stStatus.nMaxSP; }
	float GetSpeed() { return m_stStatus.fSpeed; }
	int GetStr() { return m_stStatus.nStr; }					//힘
	int GetDex() { return m_stStatus.nDex; }					//민첩성		
	int GetDef() { return m_stStatus.nDef; }					//방어력
	int GetInt() { return m_stStatus.nInt; }					//마력
	float GetCrt() { return m_stStatus.fCrt; }					//크리티컬
	int GetLevel() { return m_stStatus.nLevel; }
	float GetExp() { return m_stStatus.nExp; }

	void SetCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP = nCurrentHP; }
	void SetMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP = nMaxHP; }
	void SetCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP = nCurrentMP; }
	void SetMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP = nMaxMP; }
	void SetCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP = nCurrentSP; }
	void SetMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP = nMaxSP; }
	void SetSpeed(const float& fSpeed) { m_stStatus.fSpeed = fSpeed; }
	void SetStr(const int& nStr) { m_stStatus.nStr = nStr; }					//힘
	void SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//민첩성		
	void SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//방어력
	void SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//마력
	void SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//크리티컬
	void SetLevel(const int& nLevel) { m_stStatus.nLevel = nLevel; }
	void SetExp(const float& fExp) { m_stStatus.fExp = fExp; }
};