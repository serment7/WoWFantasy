
#pragma once
#include "cObject.h"

class cGameObject : public cObject
{
public:
	//스테이터스 정보를 일단 다 넣어봄
	int nHP;
	int nMP;
	int nSP;
	float fSpeed;

	int nStr;
	int nDef;
	int nInt;
	float fCrt;
	//필요할때마다 추가
public:
	cGameObject();
	~cGameObject();

	virtual void Update();
	virtual void Render();
	virtual void Release();
};