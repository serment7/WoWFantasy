#pragma once
#include "cGameObject.h"
class cHydra :
	public cGameObject
{
private:
	std::string folder;
	std::string filename;

public:
	cHydra();
	cHydra(const ST_STATUS& _status);
	virtual ~cHydra();

	virtual void Setup();
	virtual void Update();
	virtual void Render();
};

