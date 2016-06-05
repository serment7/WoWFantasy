
#pragma once

struct ST_STATUS
{
	//����Ʈ ����
	int nCurrentHP;
	int nMaxHP;
	int nCurrentMP;
	int nMaxMP;
	int nCurrentSP;
	int nMaxSP;
	float fSpeed;

	//�������ͽ� ����
	int nStr;					//��
	int nDex;					//��ø��		
	int nDef;					//����
	int nInt;					//����
	float fCrt;					//ũ��Ƽ��

	int nLevel;
	float fExp;

	//���۷�����
	operator+= (const ST_STATUS& stChInfo)
	{
		nCurrentHP += stChInfo.nCurrentHP;
		nMaxHP += stChInfo.nMaxHP;
		nCurrentMP += stChInfo.nCurrentMP;
		nMaxMP += stChInfo.nMaxMP;
		nCurrentSP += stChInfo.nCurrentSP;
		nMaxSP += stChInfo.nMaxSP;
		fSpeed += stChInfo.fSpeed;

		//�������ͽ� ����
		nStr += stChInfo.nStr;					//��
		nDex += stChInfo.nDex;					//��ø��		
		nDef += stChInfo.nDef;					//����
		nInt += stChInfo.nInt;					//����
		fCrt += stChInfo.fCrt;					//ũ��Ƽ��
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

		//�������ͽ� ����
		nStr -= stChInfo.nStr;					//��
		nDex -= stChInfo.nDex;					//��ø��		
		nDef -= stChInfo.nDef;					//����
		nInt -= stChInfo.nInt;					//����
		fCrt -= stChInfo.fCrt;					//ũ��Ƽ��
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

	//�������ͽ� ���úκ�
	void Setup(const ST_STATUS& stChInfo);

	void FixingStatusUp(const ST_STATUS& stChInfo);
	void FixingStatusDown(const ST_STATUS& stChInfo);

	//�������ͽ� ���� ����(�ʿ��� �ɷ�ġ �߰��� �ּ���)
	ST_STATUS GetStatus() { return m_stStatus; }

	int GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int GetMaxHP() { return m_stStatus.nMaxHP; }
	int GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int GetMaxMP() { return m_stStatus.nMaxMP; }
	int GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int GetMaxSP() { return m_stStatus.nMaxSP; }
	float GetSpeed() { return m_stStatus.fSpeed; }
	int GetStr() { return m_stStatus.nStr; }					//��
	int GetDex() { return m_stStatus.nDex; }					//��ø��		
	int GetDef() { return m_stStatus.nDef; }					//����
	int GetInt() { return m_stStatus.nInt; }					//����
	float GetCrt() { return m_stStatus.fCrt; }					//ũ��Ƽ��
	int GetLevel() { return m_stStatus.nLevel; }
	float GetExp() { return m_stStatus.nExp; }

	void SetCurrentHP(const int& nCurrentHP) { m_stStatus.nCurrentHP = nCurrentHP; }
	void SetMaxHP(const int& nMaxHP) { m_stStatus.nMaxHP = nMaxHP; }
	void SetCurrentMP(const int& nCurrentMP) { m_stStatus.nCurrentMP = nCurrentMP; }
	void SetMaxMP(const int& nMaxMP) { m_stStatus.nMaxMP = nMaxMP; }
	void SetCurrentSP(const int& nCurrentSP) { m_stStatus.nCurrentSP = nCurrentSP; }
	void SetMaxSP(const int& nMaxSP) { m_stStatus.nMaxSP = nMaxSP; }
	void SetSpeed(const float& fSpeed) { m_stStatus.fSpeed = fSpeed; }
	void SetStr(const int& nStr) { m_stStatus.nStr = nStr; }					//��
	void SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//��ø��		
	void SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//����
	void SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//����
	void SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//ũ��Ƽ��
	void SetLevel(const int& nLevel) { m_stStatus.nLevel = nLevel; }
	void SetExp(const float& fExp) { m_stStatus.fExp = fExp; }
};