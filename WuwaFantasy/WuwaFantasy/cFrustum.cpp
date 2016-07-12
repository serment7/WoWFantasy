#include "stdafx.h"
#include "cFrustum.h"


cFrustum::cFrustum()
{

}


cFrustum::~cFrustum()
{
	Release();
}


void cFrustum::SetFrustum(const D3DXMATRIXA16 & matV, const D3DXMATRIXA16 & matP)
{
	ST_PC_VERTEX v;
	v.c = D3DXCOLOR(1, 0, 0, 1);

	//0，0，0，基?で絶面体を?く
	m_vecVertex.clear();

	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, -1.0f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 1.0f, 1.0f); m_vecVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 1.0f); m_vecVertex.push_back(v);

	D3DXMATRIXA16 matVP, matInv;

	matVP = matV * matP;
	D3DXMatrixInverse(&matInv, NULL, &matVP);

	for (size_t i = 0; i < m_vecVertex.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &matInv);

	m_vPos = (m_vecVertex[0].p + m_vecVertex[5].p) / 2.0f;
	
	/*
	g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PC_VERTEX)
		, D3DUSAGE_WRITEONLY
		, ST_PC_VERTEX::FVF
		, D3DPOOL_MANAGED
		, &m_pVB
		, 0
	);
	ST_PC_VERTEX* vertices;
	m_pVB->Lock(0, 0, (LPVOID*)&vertices, 0);
	for (size_t j = 0; j < m_vecVertex.size(); ++j)
		vertices[j] = m_vecVertex[j];
	m_pVB->Unlock();
	*/

	m_vecPlane.clear();
	D3DXPLANE p;
	D3DXPlaneFromPoints(&p, &m_vecVertex[4].p, &m_vecVertex[7].p, &m_vecVertex[6].p);
	m_vecPlane.push_back(p);//top
	D3DXPlaneFromPoints(&p, &m_vecVertex[0].p, &m_vecVertex[1].p, &m_vecVertex[2].p);
	m_vecPlane.push_back(p);//bottom
	D3DXPlaneFromPoints(&p, &m_vecVertex[0].p, &m_vecVertex[4].p, &m_vecVertex[5].p);
	m_vecPlane.push_back(p);//near
	D3DXPlaneFromPoints(&p, &m_vecVertex[2].p, &m_vecVertex[6].p, &m_vecVertex[7].p);
	m_vecPlane.push_back(p);//far
	D3DXPlaneFromPoints(&p, &m_vecVertex[0].p, &m_vecVertex[3].p, &m_vecVertex[7].p);
	m_vecPlane.push_back(p);//left
	D3DXPlaneFromPoints(&p, &m_vecVertex[1].p, &m_vecVertex[5].p, &m_vecVertex[6].p);
	m_vecPlane.push_back(p);//right
}

bool cFrustum::IsIn(D3DXVECTOR3 * pV)
{
	float fDist = 0.0f;

	fDist = D3DXPlaneDotCoord(&m_vecPlane[3], pV);
	if (fDist > 0) return false;
	fDist = D3DXPlaneDotCoord(&m_vecPlane[4], pV);
	if (fDist > 0) return false;
	fDist = D3DXPlaneDotCoord(&m_vecPlane[5], pV);
	if (fDist > 0) return false;

	return true;
}

bool cFrustum::IsInSphere(BoundingSphere * sphere)
{
	float fDist = 0.0f;

	fDist = D3DXPlaneDotCoord(&m_vecPlane[3], &sphere->vCenter);
	if (fDist > sphere->fRadius) return false;
	fDist = D3DXPlaneDotCoord(&m_vecPlane[4], &sphere->vCenter);
	if (fDist > sphere->fRadius) return false;
	fDist = D3DXPlaneDotCoord(&m_vecPlane[5], &sphere->vCenter);
	if (fDist > sphere->fRadius) return false;

	return true;
}

void cFrustum::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
}

void cFrustum::Draw()
{
	/*
	g_pD3DDevice->CreateIndexBuffer(
		36 * sizeof(DWORD)
		, D3DUSAGE_WRITEONLY
		, D3DFMT_INDEX16
		, D3DPOOL_MANAGED
		, &m_pIB
		, 0
	);

	DWORD* indices = 0;
	m_pIB->Lock(0, 0, (LPVOID*)&indices, 0);

	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	indices[6] = 4; indices[7] = 7; indices[8] = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 5;

	indices[12] = 1; indices[13] = 5; indices[14] = 6;
	indices[15] = 1; indices[16] = 6; indices[17] = 2;

	indices[18] = 0; indices[19] = 3; indices[20] = 7;
	indices[21] = 0; indices[22] = 7; indices[23] = 4;

	indices[24] = 0; indices[25] = 4; indices[26] = 5;
	indices[27] = 0; indices[28] = 5; indices[29] = 1;

	indices[30] = 3; indices[31] = 7; indices[32] = 6;
	indices[33] = 3; indices[34] = 6; indices[35] = 2;

	m_pIB->Unlock();

	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PC_VERTEX));
	g_pD3DDevice->SetIndices(m_pIB);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vecVertex.size(), 0, (m_vecVertex.size() * 3) / 2);
	*/
}

void cFrustum::SetCamPos(const D3DXVECTOR3 & camPos)
{
	m_vPos = camPos;
	D3DXMATRIXA16 mat;

	//カメラの?ジション値をトレンスレ?ションしカメラのワ?ルド値を生成する
	D3DXMatrixTranslation(&mat, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = mat;
}
