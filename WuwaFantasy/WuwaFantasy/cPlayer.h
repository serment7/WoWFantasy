#pragma once
#include "cGameObject.h"

class cPlayer : 
	public cGameObject
{
private:
	std::string folder;
	std::string filename;
public:
	cPlayer();
	virtual ~cPlayer();

	void Setup();
	virtual void Update();
	virtual void Render();
};

