#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * _path)
{
	return GetTexture(std::string(_path));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string _path)
{
	if (m_mapTexture.find(_path) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;
		HRESULT hr = D3DXCreateTextureFromFileA(g_pD3DDevice,
			_path.c_str(),
			&pTexture);

		if (hr == D3D_OK)
		{
			m_mapTexture[_path] = pTexture;
		}
		else
		{
			return NULL;
		}
	}
	return m_mapTexture[_path];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetStdTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo /*= NULL*/)
{
	return GetTexture(std::string(szFullPath));
}

LPDIRECT3DTEXTURE9 cTextureManager::GetStdTexture(std::string sFullPath, D3DXIMAGE_INFO* pImageInfo /*= NULL*/)
{
	if (pImageInfo)
	{
		if (m_mapTexture.find(sFullPath) == m_mapTexture.end() ||
			m_mapImageInfo.find(sFullPath) == m_mapImageInfo.end())
		{
			SAFE_RELEASE(m_mapTexture[sFullPath]);
			D3DXCreateTextureFromFileEx(
				g_pD3DDevice,
				sFullPath.c_str(),
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT_NONPOW2,
				D3DX_DEFAULT,
				0,
				D3DFMT_UNKNOWN,
				D3DPOOL_MANAGED,
				D3DX_FILTER_NONE,
				D3DX_DEFAULT,
				0,//D3DCOLOR_XRGB(255, 255, 255),
				&m_mapImageInfo[sFullPath],
				NULL,
				&m_mapTexture[sFullPath]);
		}

		*pImageInfo = m_mapImageInfo[sFullPath];
	}
	else
	{
		if (m_mapTexture.find(sFullPath) == m_mapTexture.end())
		{
			LPDIRECT3DTEXTURE9 pTexture = NULL;
			HRESULT hr = D3DXCreateTextureFromFile(g_pD3DDevice,
				sFullPath.c_str(),
				&pTexture);

			if (hr == D3D_OK)
			{
				m_mapTexture[sFullPath] = pTexture;
			}
			else
			{
				return NULL;
			}
		}
	}

	return m_mapTexture[sFullPath];
}

void cTextureManager::Clear()
{
	Destroy();
}

void cTextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		it.second->Release();
	}
	m_mapTexture.clear();
}