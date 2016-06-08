#pragma once
#include "cGameObject.h"

class cDworfMageFSM;
struct ST_STATUS;

class cPlayer : 
	public cGameObject
{
private:
	std::string folder;
	std::string filename;

public:
	cPlayer();
	cPlayer(const ST_STATUS& _status);
	virtual ~cPlayer();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

