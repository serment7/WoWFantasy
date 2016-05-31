#pragma once
#include "cObject.h"

class cPyramid : public cObject
{
private:
	D3DXMATRIXA16 m_matWorld;
	std::vector<ST_PN_VERTEX> m_venVertex;
	D3DMATERIAL9 m_ml;

	IDirect3DVertexBuffer9* m_VB;

public:
	cPyramid();
	~cPyramid();

	void Setup(D3DXMATRIXA16* mat, D3DXCOLOR c);
	void Update();

	D3DXVECTOR3 ComputeNormal(D3DXVECTOR3* v1, D3DXVECTOR3* v2, D3DXVECTOR3* v3);
	void Render();

	void SetWorldTM(D3DXMATRIXA16 worldTM) { m_matWorld = worldTM; } 

};
