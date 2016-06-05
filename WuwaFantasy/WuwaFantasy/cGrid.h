#pragma once
#include "cGameObject.h"

//class cPyramid;

class cGrid : 
	public cGameObject
{
private:
	std::vector<ST_PC_VERTEX>				m_vecVertex;
	//std::vector<cPyramid*>				m_vecPyramid;
	//std::vector<cPyramid*>::iterator		m_iPyramid;

	IDirect3DVertexBuffer9*					m_VB;
	

public:
	cGrid();
	virtual ~cGrid();

	void Setup( int nLine = 30, float fInterval = 1.0f);
	void Render();

};