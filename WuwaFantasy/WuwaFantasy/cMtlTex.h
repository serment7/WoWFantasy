
#pragma once

class cMtlTex  
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	D3DMATERIAL9		m_stMtl;

public:
	cMtlTex();
	~cMtlTex();

	const LPDIRECT3DTEXTURE9	GetTexture() { return m_pTexture; }
	const D3DMATERIAL9			GetMtl() { return m_stMtl; }

	void SetTexture(const LPDIRECT3DTEXTURE9& pTex) { m_pTexture = pTex; }
	void SetMtl(const D3DMATERIAL9& mat) { m_stMtl = mat; } 
	void Release() { m_pTexture=nullptr; };
};