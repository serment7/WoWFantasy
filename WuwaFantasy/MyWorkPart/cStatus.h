
#pragma once

class cStatus 
{
public:
	//포인트 정보
	int nCurrentHP;
	int nMaxHP;
	int nCurrentMP;
	int nMaxMP;
	int nCurrentSP;
	int nMaxSP;
	float fCurrentSpeed;
	float fMaxSpeed;

	//스테이터스 정보
	int nStr;					//힘
	int nDex;					//민첩성		
	int nDef;					//방어력
	int nInt;					//마력
	float fCrt;					//크리티컬

public:
	cStatus();
	virtual ~cStatus();

};