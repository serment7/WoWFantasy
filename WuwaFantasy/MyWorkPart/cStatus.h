
#pragma once

class cStatus 
{
public:
	//����Ʈ ����
	int nCurrentHP;
	int nMaxHP;
	int nCurrentMP;
	int nMaxMP;
	int nCurrentSP;
	int nMaxSP;
	float fCurrentSpeed;
	float fMaxSpeed;

	//�������ͽ� ����
	int nStr;					//��
	int nDex;					//��ø��		
	int nDef;					//����
	int nInt;					//����
	float fCrt;					//ũ��Ƽ��

public:
	cStatus();
	virtual ~cStatus();

};