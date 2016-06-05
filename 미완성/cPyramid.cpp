#include "stdafx.h"
#include "cPyramid.h"


cPyramid::cPyramid()
{
	ZeroMemory(&m_ml, sizeof(D3DMATERIAL9));
}

cPyramid::~cPyramid()
{

}

void cPyramid::Setup(D3DXMATRIXA16* mat, D3DXCOLOR c)
{
	m_venVertex.clear();

	ST_PN_VERTEX v, v1, v2, v3;

	v.p = D3DXVECTOR3( 0, 0, 0); v1.p = v.p;
	v.p = D3DXVECTOR3( 1,-1,-1); v2.p = v.p;
	v.p = D3DXVECTOR3(-1,-1,-1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	v.p = D3DXVECTOR3( 0, 0, 0); v1.p = v.p;
	v.p = D3DXVECTOR3( 1,-1, 1); v2.p = v.p;
	v.p = D3DXVECTOR3( 1,-1,-1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	v.p = D3DXVECTOR3( 0, 0, 0); v1.p = v.p;
	v.p = D3DXVECTOR3(-1,-1, 1); v2.p = v.p;
	v.p = D3DXVECTOR3( 1,-1, 1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	v.p = D3DXVECTOR3( 0, 0, 0); v1.p = v.p;
	v.p = D3DXVECTOR3(-1,-1,-1); v2.p = v.p;
	v.p = D3DXVECTOR3(-1,-1, 1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	v.p = D3DXVECTOR3(-1,-1,-1); v1.p = v.p;
	v.p = D3DXVECTOR3( 1,-1,-1); v2.p = v.p;
	v.p = D3DXVECTOR3(-1,-1, 1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	v.p = D3DXVECTOR3( 1,-1,-1); v1.p = v.p;
	v.p = D3DXVECTOR3( 1,-1, 1); v2.p = v.p;
	v.p = D3DXVECTOR3(-1,-1, 1); v3.p = v.p;

	v1.n = ComputeNormal(&v1.p, &v2.p, &v3.p); m_venVertex.push_back(v1);
	v2.n = v1.n; m_venVertex.push_back(v2);
	v3.n = v1.n; m_venVertex.push_back(v3);

	if(mat)
	{
		for(size_t i = 0; i < m_venVertex.size(); ++i)
		{
			D3DXVec3TransformCoord(&m_venVertex[i].p, &m_venVertex[i].p, mat);
		}
	}

	m_ml.Ambient = m_ml.Diffuse = m_ml.Specular = c;

	g_pD3DDevice->CreateVertexBuffer(
		m_venVertex.size() * sizeof(ST_PN_VERTEX),
		0,
		ST_PC_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_VB,
		0);

	ST_PN_VERTEX* verties;

	m_VB->Lock(0, 0, (void**)&verties, 0);

	for(int i = 0; i < m_venVertex.size(); i++)
	{
		verties[i] = m_venVertex[i];
	}

	m_VB->Unlock();

}

D3DXVECTOR3 cPyramid::ComputeNormal(D3DXVECTOR3* v1, D3DXVECTOR3* v2, D3DXVECTOR3* v3)
{
	D3DXVECTOR3 vOut;
	D3DXVECTOR3 u = *v3 - *v1;
	D3DXVECTOR3 v = *v2 - *v1;

	D3DXVec3Cross(&vOut, &u, &v);
	D3DXVec3Normalize(&vOut, &vOut);

	return vOut;
}

void cPyramid::Update()
{	
	D3DXMATRIX matR, matT;

	D3DXMatrixLookAtLH(&matR,
		&D3DXVECTOR3(0, 0 ,0),
		&GetVDir(),
		&D3DXVECTOR3(0, 1, 0));

	D3DXMatrixTranspose(&matR, &matR);
	//SetScaling(1, 1, 1);
	//SetRotationMatirx(matR);
	Update();

	m_matWorld = matR;
}

void cPyramid::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pD3DDevice->SetMaterial(&m_ml);

	g_pD3DDevice->SetStreamSource(0, m_VB, 0, sizeof(ST_PN_VERTEX));
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	g_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, true);
	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		m_venVertex.size() / 3
		);
}