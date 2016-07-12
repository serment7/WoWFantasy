#include "stdafx.h"
#include "cUIProgressButton.h"

cUIProgressButton::cUIProgressButton()
{
}

cUIProgressButton::~cUIProgressButton()
{
}

void cUIProgressButton::Setup(int x, int y, int width, int height)
{
	m_nX = x;
	m_nY = y;
	//Draw Image Position
	RECT rc;
	if (SetRect(&rc, 0, 0, width, height))
	{
		assert("Create Rect is FAILED");
		return;
	}
	m_nRcBottom = m_nRcTop = rc;

	//Primery Texture File Regist in Manager
	D3DXIMAGE_INFO nBarInfo;
	m_nProgressBarBottom = g_pSpriteManager->GetTexture("./Resource/UI/progressTop.png", nBarInfo);
	m_nProgressBarTop = g_pSpriteManager->GetTexture("./Resource/UI/progressBottom.png", nBarInfo);
	m_nBarInfo = nBarInfo;

	m_fHeight = height;
	D3DXMatrixIdentity(&m_matSprite);
	m_matSprite._41 = x;
	m_matSprite._42 = y;
	m_matSprite._11 = 6;

}

void cUIProgressButton::Setup(const std::string& szUpImageFileName, const std::string& szDownImageFileName, int x, int y, int width, int height)
{
	m_nX = x;
	m_nY = y;

	//Draw Image Position
	RECT rc;
	if (!SetRect(&rc, 0, 0, width, height))
	{
		assert("Create Rect is FAILED");
		return;
	}
	m_nRcBottom = m_nRcTop = rc;

	//File Name Definition
	std::string sButtom(szDownImageFileName);
	std::string sTop(szUpImageFileName);

	//User Texture File Regist in Manager
	D3DXIMAGE_INFO nBarInfo;
	m_nProgressBarBottom = g_pSpriteManager->GetTexture(sButtom, nBarInfo);
	m_nProgressBarTop = g_pSpriteManager->GetTexture(sTop, nBarInfo);
	m_nBarInfo = nBarInfo;

	m_fHeight = height;

	D3DXMatrixIdentity(&m_matSprite);
	m_matSprite._41 = x;
	m_matSprite._42 = y;

}

void cUIProgressButton::Release()
{

}

void cUIProgressButton::Update()
{
	SetRect(&m_nRcTop, 0, 0, m_nBarInfo.Width, m_fHeight);
	cUIObject::UpdateWorldTM();

	if (GetKeyState(GetTag()) & 0x8000)
	{
		if (m_pDelegate)
		{
			m_pDelegate->OnClick(this);
		}
	}

	cUIObject::UpdateChildren();
}

void cUIProgressButton::Render(LPD3DXSPRITE pSprite)
{
	g_pSpriteManager->BeginSprite();
	g_pSpriteManager->SetTransform(m_matWorld);

	g_pSpriteManager->Draw(m_nProgressBarBottom, m_nRcBottom, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0.5f), D3DXCOLOR(1, 1, 1, 1));
	g_pSpriteManager->Draw(m_nProgressBarTop, m_nRcTop, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0.3f), D3DXCOLOR(1, 1, 1, 1));
	g_pSpriteManager->EndSprite();

	cUIObject::Render(pSprite);
}

void cUIProgressButton::SetGuage(float currentGauge, float maxGauge)
{
	m_fHeight = (currentGauge / maxGauge) * m_nBarInfo.Height;

	m_nRcTop.top = m_nRcTop.bottom - m_fHeight;
}
