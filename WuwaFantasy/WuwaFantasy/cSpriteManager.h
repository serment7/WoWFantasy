#pragma once

#define g_pSpriteManager cSpriteManager::GetInstance()

class cSpriteManager
{
private:
	LPD3DXSPRITE		m_pSprite;
	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

public:
	cSpriteManager();
	~cSpriteManager();

	static cSpriteManager* GetInstance()
	{
		static cSpriteManager instance;
		return &instance;
	}

	void Clear();
	void Destroy();
	void BeginSprite();
	void BeginSprite(const DWORD& _flag);
	void EndSprite();

	LPDIRECT3DTEXTURE9 GetTexture(char* _path, OUT D3DXIMAGE_INFO& _image_info);
	LPDIRECT3DTEXTURE9 GetTexture(std::string _path, OUT D3DXIMAGE_INFO& _image_info);

	void Draw(const LPDIRECT3DTEXTURE9 & _texture, const RECT & _rc, const D3DXVECTOR3 & _center, const D3DXVECTOR3 & _pos, const D3DCOLOR & _color);
	void SetTransform(const D3DXMATRIXA16&);
};