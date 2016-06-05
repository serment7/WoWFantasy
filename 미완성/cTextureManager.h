#pragma once
class cTextureManager
{
private:

	std::map<std::string, LPDIRECT3DTEXTURE9> m_mapTexture;

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

	void Clear();
	void Destroy();
};

