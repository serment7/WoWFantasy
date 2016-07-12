
#pragma once

class cHmap
{
private:
	
	IDirect3DIndexBuffer9* m_pIB;

	D3DMATERIAL9 m_ml;

	LPDIRECT3DTEXTURE9 m_nVer;
	std::vector<ST_PNT_VERTEX> m_vecPnt;

	std::vector<int> m_vecHeight;

	int m_mapSize;
	int count;

	std::vector<int> m_vecIndex;

public:
	IDirect3DVertexBuffer9* m_pVB;
	cHmap();
	~cHmap();

	void Setup(int mapSize);
	void CalcNormalVec(D3DXVECTOR3* vResult, D3DXVECTOR3* v0, D3DXVECTOR3* v1, D3DXVECTOR3* v2);
	void CalcNormal(D3DXVECTOR3* vResult, int index, ST_PNT_VERTEX* verties);

	void CalcTerrainHeight(IN float chX, OUT float* chY, IN float chZ);

	void Release();
	void FrustumCallingUpdate();
	void Render();

};
