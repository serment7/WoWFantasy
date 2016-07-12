#pragma once
#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:

	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;
	std::map<std::string, D3DXIMAGE_INFO>		m_mapImageInfo;

public:
	cTextureManager();
	~cTextureManager();

	static cTextureManager* GetInstance()
	{
		static cTextureManager instance;
		return &instance;
	}

	LPDIRECT3DTEXTURE9 GetTexture(char * _path);
	LPDIRECT3DTEXTURE9 GetTexture(std::string _path);

	LPDIRECT3DTEXTURE9 GetStdTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo = NULL);
	LPDIRECT3DTEXTURE9 GetStdTexture(std::string sFullPath, D3DXIMAGE_INFO* pImageInfo = NULL);

	void Clear();
	void Destroy();
};

