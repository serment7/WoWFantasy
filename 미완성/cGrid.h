#pragma once

class cPyramid;

class cGrid  
{
private:
	std::vector<ST_PC_VERTEX>				m_vecVertex;
	std::vector<cPyramid*>					m_vecPyramid;
	std::vector<cPyramid*>::iterator		m_iPyramid;

	IDirect3DVertexBuffer9*					m_VB;
	

public:
	cGrid();
	~cGrid();

	void Setup( int nLine = 30, float fInterval = 1.0f);
	void Render();

};