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