
#include "StdAfx.h"
#include "cGrid.h"
//#include "cPyramid.h"

cGrid::cGrid(void)
{
	this->AddRef();
}

cGrid::~cGrid(void)
{
	SAFE_RELEASE(m_VB);
}

void cGrid::Setup( float nLine /*= 30*/, float fInterval /*= 1.0f*/ )
{
	float fNumLine = (float)(nLine / 2);

	float fMax = fNumLine * fInterval;

	ST_PC_VERTEX v;
	
	for (int i = 1; i <= fNumLine; ++i)
	{
		if (i % 5 == 0)
		{
			v.c = D3DCOLOR_XRGB(255, 255, 255);
		}
		else
		{
			v.c = D3DCOLOR_XRGB(128, 128, 128);
		}
		v.p = D3DXVECTOR3(-fMax, 0, i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3( fMax, 0, i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-fMax, 0,-i * fInterval); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3( fMax, 0,-i * fInterval); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3( i * fInterval, 0,-fMax); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3( i * fInterval, 0, fMax); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(-i * fInterval, 0,-fMax); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-i * fInterval, 0, fMax); m_vecVertex.push_back(v);
	}

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-fMax, 0, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( fMax, 0, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	v.p = D3DXVECTOR3( 0,-fMax, 0); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 0, fMax, 0); m_vecVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	v.p = D3DXVECTOR3( 0, 0,-fMax); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3( 0, 0, fMax); m_vecVertex.push_back(v);

	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_VB,
		0);

	ST_PC_VERTEX* verties;

	m_VB->Lock(0, 0, (void**)&verties, 0);

	for(size_t j = 0; j < m_vecVertex.size(); j++)
	{
		verties[j] = m_vecVertex[j];
	}

	m_VB->Unlock();


	/*
	D3DXMATRIXA16 matR, matS, matWorld;

	D3DXMatrixScaling(&matS, 0.2f, 2.f, 0.2f);
	
	//x ÁE
	D3DXMatrixRotationZ(&matR, D3DX_PI / 2.0f);
	
	matWorld = matS * matR;
	
	cPyramid* pPyramid = new cPyramid;
	pPyramid->Setup(&matWorld, D3DCOLOR_XRGB(255, 0, 0));
	m_vecPyramid.push_back(pPyramid);

	//y ÁE
	D3DXMatrixRotationZ(&matR, D3DX_PI);

	matWorld = matS * matR;

	pPyramid = new cPyramid;
	pPyramid->Setup(&matWorld, D3DCOLOR_XRGB(0, 255, 0));
	m_vecPyramid.push_back(pPyramid);


	//z ÁE
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;

	pPyramid = new cPyramid;
	pPyramid->Setup(&matWorld, D3DCOLOR_XRGB(0, 0, 255));
	m_vecPyramid.push_back(pPyramid);
	*/
	ST_PNT_VERTEX triVertex;
	ZeroMemory(&triVertex, sizeof(triVertex));
	triVertex.p = D3DXVECTOR3(-fMax,0, -fMax);
	m_TriVertex.push_back(triVertex);
	triVertex.p = D3DXVECTOR3(-fMax, 0, fMax);
	m_TriVertex.push_back(triVertex);
	triVertex.p = D3DXVECTOR3(fMax, 0, -fMax);
	m_TriVertex.push_back(triVertex);
	triVertex.p = D3DXVECTOR3(fMax, 0, -fMax);
	m_TriVertex.push_back(triVertex);
	triVertex.p = D3DXVECTOR3(-fMax, 0, fMax);
	m_TriVertex.push_back(triVertex);
	triVertex.p = D3DXVECTOR3(fMax, 0, fMax);
	m_TriVertex.push_back(triVertex);
}

void cGrid::Render()
{
	D3DXMATRIXA16 matWorld;

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetStreamSource(0, m_VB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->SetTexture(0, 0);

	g_pD3DDevice->DrawPrimitive(
		D3DPT_LINELIST,
		0,
		m_vecVertex.size() / 2
		);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	
	/*
	for(m_iPyramid = m_vecPyramid.begin(); m_iPyramid != m_vecPyramid.end(); ++m_iPyramid)
	{
		(*m_iPyramid)->Render();
	}
	*/
}

void cGrid::Release()
{
	m_VB->Release();
	cGameObject::Release();
}

std::vector<ST_PNT_VERTEX>& cGrid::GetTriVertex()
{
	return m_TriVertex;
}
