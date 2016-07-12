#pragma once
#include "cUIObject.h"

class cUIProgressButton;
class iUIProgressButtonDelegate
{
public:
	virtual void OnClick(cUIProgressButton* pSender) = 0;
};
class cUIProgressButton : public cUIObject
{
private:
	int m_nX;
	int m_nY;
	float m_fHeight;

	RECT m_nRcBottom;
	RECT m_nRcTop;

	D3DXIMAGE_INFO m_nBarInfo;

	LPDIRECT3DTEXTURE9 m_nProgressBarBottom;
	LPDIRECT3DTEXTURE9 m_nProgressBarTop;

	D3DXMATRIX m_matSprite;

protected:

	SYNTHESIZE(iUIProgressButtonDelegate*, m_pDelegate, Delegate);
public:
	cUIProgressButton();
	~cUIProgressButton();

	void Setup(int x, int y, int width, int height);
	void Setup(const std::string& szUpImageFileName, const std::string& szDownImageFileName, int x, int y, int width, int height);

	virtual void Release();
	virtual void Update();
	virtual void Render(LPD3DXSPRITE pSprite);

	void SetGuage(float currentGauge, float maxGauge);

	void SetX(int x) { m_nX = x; }
	void SetY(int y) { m_nY = y; }
};