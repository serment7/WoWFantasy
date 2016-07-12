
#include "stdafx.h"
#include "cHmap.h"
#include <iostream>

cHmap::cHmap()
	: 	m_pVB(NULL),
		m_pIB(NULL)
{
	count = 0;
}

cHmap::~cHmap()
{

}

void cHmap::Setup(int mapSize)
{
//	m_pQuadTree = new cQuadTree(mapSize);

	FILE* file;
	fopen_s(&file, "./Resource/Mode/output.raw", "rb");

	int i = 0;
	int result = 0;

	while (!feof(file))
	{
		fscanf_s(file, "%c", &result);
		m_vecHeight.push_back(result);
	}
	
	m_mapSize = mapSize + 1;
	g_pD3DDevice->CreateVertexBuffer(
		m_mapSize * m_mapSize * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0);

	g_pD3DDevice->CreateIndexBuffer(
		m_mapSize * m_mapSize * 6 * sizeof(int),
		0,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_pIB,
		0);

	HRESULT hr = D3DXCreateTextureFromFile(g_pD3DDevice, "./Resource/Mode/terrain.png", &m_nVer);

	//πˆ≈ÿΩ∫∏¶ ¬ÅE˚›÷∞ÅE
	ST_PNT_VERTEX* verties;
	ST_PNT_VERTEX pnt;

	float coodinateVertexPoint = 1.0f / mapSize;
	float normalHeightY = 0.0f;
	
	m_pVB->Lock(0, 0, (void**)&verties, 0);


	for(int vz = 0; vz < m_mapSize; vz++)
	{
		for(int vx = 0; vx < m_mapSize; vx++)
		{
			normalHeightY = (float)m_vecHeight[vx + m_mapSize * vz];

			pnt.p = D3DXVECTOR3(vx, normalHeightY, vz);
			pnt.u = vx * coodinateVertexPoint;
			pnt.v =	vz * coodinateVertexPoint;

			m_vecPnt.push_back(pnt);
			verties[vx + (m_mapSize * vz)] = pnt;
		}
	}

	for(int t = 0; t < m_mapSize * m_mapSize; t++)
	{
		CalcNormal(&verties[t].n, t, verties);
	}

	m_pVB->Unlock();

	m_ml.Ambient = m_ml.Diffuse = m_ml.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_ml.Emissive = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	m_ml.Power = 7.0f;

	fclose(file);
}

void cHmap::CalcNormalVec(D3DXVECTOR3* vResult, D3DXVECTOR3* v0, D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	D3DXVECTOR3 vector;
	D3DXVECTOR3 A = *v2 - *v0;
	D3DXVECTOR3 B = *v1 - *v0;

	D3DXVec3Cross(&vector, &A, &B);

	D3DXVec3Normalize(&vector, &vector);

	*vResult = vector;
}

void cHmap::CalcNormal(D3DXVECTOR3* vResult, int index, ST_PNT_VERTEX* verties)
{
	int mapSize = m_mapSize - 1;
	int degree = index / m_mapSize;
	float expMapSize = (float)mapSize / m_mapSize;
	float findex = ((float)index / m_mapSize) - degree;

	D3DXVECTOR3 Result;

	//≈◊µŒ∏Æ ≥—πˆ∏¶ ∞ÀªÅE
	if((int)index / m_mapSize <= 0 || (int)index / m_mapSize >= mapSize)
	{
		Result = D3DXVECTOR3(0, 1, 0);

		D3DXVec3Normalize(&Result, &Result);
		*vResult = Result;
		return;
	}

	if(findex >= (expMapSize - 0.000007) || findex <= 0.0f)
	{

		Result = D3DXVECTOR3(0, 1, 0);

		D3DXVec3Normalize(&Result, &Result);
		*vResult = Result;
		return;
	}
	//πÿø°≤≤ ¿˚øÅE?æ»µ«¥¬∞≈ ∞∞¿∏¥œ 6∞≥¿« ∆Ú±’¿Ã≥™ ±∏«ÿ ∫ª¥Ÿ.


	//ø©±‚±˚?E≥—æ˚€‘¿∏∏ÅE∞ËªÅE
	D3DXVECTOR3 A = verties[index + 1].p - verties[index - 1].p;
	D3DXVECTOR3 B = verties[index + m_mapSize].p - verties[abs(index - m_mapSize)].p;

	D3DXVec3Cross(&Result, &A, &B);

	D3DXVec3Normalize(&Result, &Result);

	*vResult = Result;

	return;


}

void cHmap::Release()
{
	SAFE_RELEASE(m_pVB);
	SAFE_RELEASE(m_pIB);
	SAFE_RELEASE(m_nVer);
}

void cHmap::FrustumCallingUpdate()
{
	//¿Œµ¶Ω∫∏¶ ¡ˆ¡§«—¥Ÿ
	int* indices = NULL;
	int index = 0;

	int mapSize = m_mapSize - 1;

	m_pIB->Lock(0, 0, (void**)&indices, 0);

	for (int m = 0; m < mapSize; m++)
	{
		for (int n = 0; n < mapSize; n++)
		{
			indices[index] = m * m_mapSize + n;
			indices[index + 1] = (m + 1) * m_mapSize + n;
			indices[index + 2] = m * m_mapSize + (n + 1);

			indices[index + 3] = (m + 1) * m_mapSize + n;
			indices[index + 4] = (m + 1) * m_mapSize + (n + 1);
			indices[index + 5] = m * m_mapSize + (n + 1);

			index += 6;
		}
	}

	/*
	for (int m = 0; m < mapSize; m++)
	{
		for (int n = 0; n < mapSize; n++)
		{
			if (g_pGameManager->GetCamera()->IsIn(m_vecPnt[m * mapSize + n].p)) continue;
			indices[index] = m * m_mapSize + n;
			indices[index + 1] = (m + 1) * m_mapSize + n;
			indices[index + 2] = m * m_mapSize + (n + 1);

			indices[index + 3] = (m + 1) * m_mapSize + n;
			indices[index + 4] = (m + 1) * m_mapSize + (n + 1);
			indices[index + 5] = m * m_mapSize + (n + 1);

			index += 6;
		}
	}*/
	m_pIB->Unlock();
}

void cHmap::Render()
{

	D3DXMATRIXA16 matT;

	D3DXMatrixIdentity(&matT);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matT);

	g_pD3DDevice->SetMaterial(&m_ml);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	g_pD3DDevice->SetTexture(0, m_nVer);

	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));

	g_pD3DDevice->SetIndices(m_pIB);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

	g_pD3DDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,
		0,
		0,
		m_mapSize * m_mapSize,
		0,
		m_mapSize * m_mapSize * 2
	);
}

void cHmap::CalcTerrainHeight(IN float chX, OUT float* chY, IN float chZ)
{
	int indexPointX = chX / 1.0f;
	int indexPointZ = chZ / 1.0f;

	if(indexPointX <= 0 || indexPointZ <= 0)
	{
		*chY = 0.0f;
		return;
	}

	int point1 = indexPointZ * m_mapSize + indexPointX;
	int point2 = (indexPointZ + 1) * m_mapSize + indexPointX;
	int point3 = indexPointZ * m_mapSize + (indexPointX + 1);
	int point4 = (indexPointZ + 1) * m_mapSize + (indexPointX + 1);

	D3DXVECTOR3 p0 = m_vecPnt[point1].p;
	D3DXVECTOR3 p1 = m_vecPnt[point2].p;
	D3DXVECTOR3 p2 = m_vecPnt[point3].p;
	D3DXVECTOR3 p3 = m_vecPnt[point4].p;
	D3DXVECTOR3 vResult;

	float deltaX = (chX - p0.x) / 1.0f;
	float deltaZ = (chZ - p0.z) / 1.0f;

	if(deltaX + deltaZ <= 1)
	{
		vResult = p0 + (p2 - p0) * deltaX + (p1 - p0) * deltaZ;
		*chY = vResult.y;
	}
	else
	{
		deltaX = 1 - deltaX;
		deltaZ = 1 - deltaZ;
		vResult = p3 + (p2 - p3) * deltaX + (p1 - p3) * deltaZ;
		*chY = vResult.y;
	}
}