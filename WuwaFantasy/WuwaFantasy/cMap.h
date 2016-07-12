#pragma once

class cMap
{
private:
	std::string						m_strParse;

	LPD3DXMESH						m_pMesh;
	D3DMATERIAL9					m_stMtl;
	int								m_nHPixel;
	std::vector<ST_PNT_VERTEX>		m_vecVertex;

	LPDIRECT3DINDEXBUFFER9			m_pIndexBuf;

	LPDIRECT3DTEXTURE9				m_pTexture = nullptr;

	int								m_nBytePerPixel = 1;
public:
	cMap(const std::string& _mappath, const std::string& _texturepath);
	~cMap();
	bool CalcHeight(float x, float & y, float z);
	void Render();

	std::vector<ST_PNT_VERTEX>&		GetTriVertex();
};

