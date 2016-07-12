#pragma once

#define g_pFontManager cFontManager::GetInstance()

class cFontManager
{

public:
	static cFontManager* GetInstance()
	{
		static cFontManager instance;
		return &instance;
	}

public:
	enum eFontType
	{
		E_FONT_NORMAL,
		E_FONT_QUEST,
		E_FONT_NAME
	};
private:
	std::map<eFontType, LPD3DXFONT> m_mapFont;


	cFontManager();
	~cFontManager();
public:
	LPD3DXFONT GetFont(eFontType e);
	void Destroy();
};

