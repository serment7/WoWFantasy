#pragma once

class cFrustum
{
private:
	std::vector<ST_PC_VERTEX>	m_vecVertex;
	D3DXVECTOR3					m_vPos;
	std::vector<D3DXPLANE>		m_vecPlane;
	D3DXMATRIXA16				m_matWorld;

	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

public:
	cFrustum();
	~cFrustum();

	void SetFrustum(const D3DXMATRIXA16& matV, const D3DXMATRIXA16& matP);
	bool IsIn(D3DXVECTOR3* pV);
	bool IsInSphere(BoundingSphere* sphere);
	void Release();
	void Draw();

	void SetCamPos(const D3DXVECTOR3& camPos);
	const D3DXVECTOR3& GetCamPos() { return m_vPos; }
};

