#include "stdafx.h"
#include "cMap.h"
#include "cParsing.h"

const std::string MAP_PATH = "./Resource/Mode/";

cMap::cMap(const std::string& _rawpath, const std::string& _texturepath)
{
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = m_stMtl.Diffuse = m_stMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pTexture);

	FILE* fp = NULL;
	std::string fullpath = MAP_PATH.substr() + _rawpath.substr();
	std::string texturepath= MAP_PATH.substr() + _texturepath.substr();
	fopen_s(&fp, fullpath.c_str(), "rb");

	m_pTexture = g_pTextureManager->GetTexture(texturepath);

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int nPixel = nFileSize / m_nBytePerPixel;
	int nHPixel = (int)sqrt((float)nPixel + EPSILON);
	//assert(nHPixel * nHPixel == nPixel && "정사각 형태의 raw파일만 사용 가능함");

	m_nHPixel = nHPixel;

	std::vector<BYTE> vecHeight(nPixel*nHPixel);

	for (int i = 0; i < nPixel; ++i)
	{
		vecHeight[i] = (BYTE)fgetc(fp);
		if (m_nBytePerPixel > 1)
		{
			fseek(fp, m_nBytePerPixel - 1, SEEK_CUR);
		}
	}

	int nTileN = nHPixel - 1;

	m_vecVertex.resize(nPixel);
	for (int z = 0; z < nHPixel; ++z)
	{
		for (int x = 0; x < nHPixel; ++x)
		{
			int i = z * nHPixel + x;

			ST_PNT_VERTEX v;
			v.p = D3DXVECTOR3((float)x, vecHeight[i], (float)z);
			v.u = x / (float)nTileN;
			v.v = z / (float)nTileN;
			v.n = D3DXVECTOR3(0, 1, 0);

			m_vecVertex[i] = v;
		}
	}

	for (int z = 1; z < nTileN; ++z)
	{
		for (int x = 1; x < nTileN; ++x)
		{
			int i = z * nHPixel + x;
			int l = i - 1;
			int r = i + 1;
			int u = i + nHPixel;
			int d = i - nHPixel;

			D3DXVECTOR3 lr = m_vecVertex[r].p - m_vecVertex[l].p;
			D3DXVECTOR3 du = m_vecVertex[u].p - m_vecVertex[d].p;
			D3DXVECTOR3 n;
			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);
			m_vecVertex[i].n = n;
		}
	}

	// 1--3
	// |\ |
	// | \|
	// 0--2
	std::vector<DWORD> vecIndex;
	vecIndex.reserve(nTileN * nTileN * 3 * 2);

	for (int z = 0; z < nTileN; ++z)
	{
		for (int x = 0; x < nTileN; ++x)
		{
			int _0 = (z + 0) * nHPixel + x;
			int _1 = (z + 1) * nHPixel + x;
			int _2 = (z + 0) * nHPixel + x + 1;
			int _3 = (z + 1) * nHPixel + x + 1;
			vecIndex.push_back(_0); vecIndex.push_back(_1); vecIndex.push_back(_2);
			vecIndex.push_back(_3); vecIndex.push_back(_2); vecIndex.push_back(_1);
		}
	}


	D3DXCreateMeshFVF(vecIndex.size() / 3,
		m_vecVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT,
		ST_PNT_VERTEX::FVF,
		g_pD3DDevice,
		&m_pMesh);

	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &m_vecVertex[0], sizeof(ST_PNT_VERTEX) * m_vecVertex.size());
	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], sizeof(DWORD) * vecIndex.size());
	m_pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, sizeof(DWORD) * m_pMesh->GetNumFaces());
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdjBuf(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(0.0f, &vecAdjBuf[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdjBuf[0],
		0, 0, 0);

	fclose(fp);
}

cMap::~cMap()
{
	int n=m_pMesh->Release();
}


void cMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
}

std::vector<ST_PNT_VERTEX>& cMap::GetTriVertex()
{
	return m_vecVertex;
}

bool cMap::CalcHeight(float x, float& y, float z)
{
	if (x < 0 || z < 0 || x > m_nHPixel - 1 || z > m_nHPixel - 1)
		return false;

	// 1--3
	// |\ |
	// | \|
	// 0--2
	int nx = (int)x;
	int nz = (int)z;
	int _0 = (nz + 0) * m_nHPixel + nx;
	int _1 = (nz + 1) * m_nHPixel + nx;
	int _2 = (nz + 0) * m_nHPixel + nx + 1;
	int _3 = (nz + 1) * m_nHPixel + nx + 1;

	float dx = x - nx;
	float dz = z - nz;
	if (dx + dz < 1)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1].p - m_vecVertex[_0].p;
		D3DXVECTOR3 v02 = m_vecVertex[_2].p - m_vecVertex[_0].p;

		y = (v01 * dz + v02 * dx + m_vecVertex[_0].p).y;
	}
	else
	{
		dx = 1.0f - dx;
		dz = 1.0f - dz;

		D3DXVECTOR3 v31 = m_vecVertex[_1].p - m_vecVertex[_3].p;
		D3DXVECTOR3 v32 = m_vecVertex[_2].p - m_vecVertex[_3].p;

		y = (v31 * dx + v32 * dz + m_vecVertex[_3].p).y;
	}
	return true;
}
