
#pragma once

struct ST_STATUS
{
	//����Ʈ ����
	int nCurrentHP = 0;
	int nMaxHP = 0;
	int nCurrentMP = 0;
	int nMaxMP = 0;
	int nCurrentSP = 0;
	int nMaxSP = 0;
	float fSpeed = 0.0f;

	//�������ͽ� ����
	int nStr = 0;					//?E
	int nDex = 0;					//��ø��		
	int nDef = 0;					//�����
	int nInt = 0;					//����
	float fCrt = 0.0f;					//ũ��Ƽ��

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

	//�������ͽ� ���úκ�
	void Setup(const ST_STATUS& stChInfo);

	//�������ͽ� ���� ����(�ʿ��� �ɷ�ġ �߰��� �ּ���E
	ST_STATUS GetStatus() { return m_stStatus; }

	int		GetCurrentHP() { return m_stStatus.nCurrentHP; }
	int		GetMaxHP() { return m_stStatus.nMaxHP; }
	int		GetCurrentMP() { return m_stStatus.nCurrentMP; }
	int		GetMaxMP() { return m_stStatus.nMaxMP; }
	int		GetCurrentSP() { return m_stStatus.nCurrentSP; }
	int		GetMaxSP() { return m_stStatus.nMaxSP; }
	float	GetSpeed() const { return m_stStatus.fSpeed; }
	int		GetStr() { return m_stStatus.nStr; }					//?E
	int		GetDex() { return m_stStatus.nDex; }					//��ø��		
	int		GetDef() { return m_stStatus.nDef; }					//�����
	int		GetInt() { return m_stStatus.nInt; }					//����
	float	GetCrt() { return m_stStatus.fCrt; }					//ũ��Ƽ��
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
	void	SetDex(const int& nDex) { m_stStatus.nDex = nDex; }					//��ø��		
	void	SetDef(const int& nDef) { m_stStatus.nDef = nDef; }					//�����
	void	SetInt(const int& nInt) { m_stStatus.nInt = nInt; }					//����
	void	SetCrt(const float& fCrt) { m_stStatus.fCrt = fCrt; }					//ũ��Ƽ��
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
	void	IncDex(const int& nDex) { m_stStatus.nDex += nDex; }					//��ø��		
	void	IncDef(const int& nDef) { m_stStatus.nDef += nDef; }					//�����
	void	IncInt(const int& nInt) { m_stStatus.nInt += nInt; }					//����
	void	IncCrt(const float& fCrt) { m_stStatus.fCrt += fCrt; }					//ũ��Ƽ��
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
	void	DecDex(const int& nDex) { m_stStatus.nDex -= nDex; }					//��ø��		
	void	DecDef(const int& nDef) { m_stStatus.nDef -= nDef; }					//�����
	void	DecInt(const int& nInt) { m_stStatus.nInt -= nInt; }					//����
	void	DecCrt(const float& fCrt) { m_stStatus.fCrt -= fCrt; }					//ũ��Ƽ��
	void	DecLevel(const int& nLevel) { m_stStatus.nLevel -= nLevel; }
	void	DecExp(const float& fExp) { m_stStatus.fExp -= fExp; }
};