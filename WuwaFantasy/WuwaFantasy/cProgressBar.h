#pragma once

class cProgressBar
{
private:
	int m_nX;
	int m_nY;
	float m_fWidth;

	RECT m_nRcBottom;
	RECT m_nRcTop;

	D3DXIMAGE_INFO m_nBarInfo;

	LPDIRECT3DTEXTURE9 m_nProgressBarBottom;
	LPDIRECT3DTEXTURE9 m_nProgressBarTop;

	D3DXMATRIX m_matSprite;


public:
	cProgressBar();
	~cProgressBar();

	void Setup(int x, int y, int width, int height);
	void Setup(char* szUpImageFileName, char* szDownImageFileName, int x, int y, int width, int height);

	void Release();
	void Update();
	void Render();

	void SetGuage(float currentGauge, float maxGauge);

	void SetX(int x) { m_nX = x; }
	void SetY(int y) { m_nY = y; }
};