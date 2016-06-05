#pragma once
#include "cGameObject.h"

class cPlayer : 
	public cGameObject
{
private:

public:
	cPlayer();
	virtual ~cPlayer();

	void Setup();
	virtual void Update();
	virtual void Render();
};

