#include "stdafx.h"
#include "cProgressBar.h"

cProgressBar::cProgressBar()
{
}

cProgressBar::~cProgressBar()
{
}

void cProgressBar::Setup(int x, int y, int width, int height)
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

	m_fWidth = width;
	D3DXMatrixIdentity(&m_matSprite);
	m_matSprite._41 = x;
	m_matSprite._42 = y;
	m_matSprite._11 = 6;

}

void cProgressBar::Setup(char * szUpImageFileName, char * szDownImageFileName, int x, int y, int width, int height)
{
	m_nX = x;
	m_nY = y;

	//Draw Image Position
	RECT rc;
	if(!SetRect(&rc, 0, 0, width, height))
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

	m_fWidth = width;

	D3DXMatrixIdentity(&m_matSprite);
	m_matSprite._41 = x;
	m_matSprite._42 = y;

}

void cProgressBar::Release()
{

}

void cProgressBar::Update()
{
	SetRect(&m_nRcTop, 0, 0, m_fWidth, m_nBarInfo.Height);
}

void cProgressBar::Render()
{
	g_pSpriteManager->BeginSprite();
	g_pSpriteManager->SetTransform(m_matSprite);
	
	g_pSpriteManager->Draw(m_nProgressBarBottom, m_nRcBottom, D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 0.2f), D3DXCOLOR(1, 1, 1, 1));
	g_pSpriteManager->Draw(m_nProgressBarTop, m_nRcTop, D3DXVECTOR3(0,0,0), D3DXVECTOR3(0,0,0), D3DXCOLOR(1, 1, 1, 1));
	g_pSpriteManager->EndSprite();
}

void cProgressBar::SetGuage(float currentGauge, float maxGauge)
{
	m_fWidth = (currentGauge / maxGauge) * m_nBarInfo.Width;

	m_nRcTop.right = m_nRcTop.left + m_fWidth;
}
