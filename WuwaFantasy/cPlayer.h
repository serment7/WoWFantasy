#pragma once
#include "cGameObject.h"

class cPlayer : 
	public cGameObject
{
private:

public:
	cPlayer();
	~cPlayer();

	void Setup();
	void Update();
	void Render();
	void Release();
};

