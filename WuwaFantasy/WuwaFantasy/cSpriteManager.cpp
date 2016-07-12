#include "stdafx.h"
#include "cSpriteManager.h"

cSpriteManager::cSpriteManager()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

cSpriteManager::~cSpriteManager()
{

}

void cSpriteManager::Clear()
{
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();
}

void cSpriteManager::Destroy()
{
	Clear();
	SAFE_RELEASE(m_pSprite);
}

void cSpriteManager::BeginSprite()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
}

void cSpriteManager::BeginSprite(const DWORD & _flag)
{
	m_pSprite->Begin(_flag);
}

void cSpriteManager::EndSprite()
{
	m_pSprite->End();
}

LPDIRECT3DTEXTURE9 cSpriteManager::GetTexture(char * _path, OUT D3DXIMAGE_INFO& _image_info)
{
	return GetTexture(std::string(_path), _image_info);
}

LPDIRECT3DTEXTURE9 cSpriteManager::GetTexture(std::string _path, OUT D3DXIMAGE_INFO& _image_info)
{
	if (m_mapTexture.find(_path) == m_mapTexture.end())
	{
		LPDIRECT3DTEXTURE9 pTexture = NULL;

		HRESULT hr = D3DXCreateTextureFromFileEx(
			g_pD3DDevice,
			_path.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&_image_info,
			NULL,
			&pTexture);
		if (hr == D3D_OK)
		{
			m_mapTexture[_path] = pTexture;
			m_mapInfo[_path] = _image_info;
		}
		else
		{
			return NULL;
		}
	}
	if (m_mapInfo.find(_path) != m_mapInfo.end())
		_image_info = m_mapInfo[_path];
	return m_mapTexture[_path];
}

void cSpriteManager::Draw(const LPDIRECT3DTEXTURE9 & _texture, const RECT & _rc, const D3DXVECTOR3 & _center, const D3DXVECTOR3 & _pos, const D3DCOLOR & _color)
{
	m_pSprite->Draw(_texture,
		&_rc,
		&_center,
		&_pos,
		_color);
}

void cSpriteManager::SetTransform(const D3DXMATRIXA16 & _transform)
{
	m_pSprite->SetTransform(&_transform);
}