#include "StdAfx.h"
#include "cMiniMapImageView.h"


cMiniMapImageView::cMiniMapImageView(void)
{
}


cMiniMapImageView::~cMiniMapImageView(void)
{
}

void cMiniMapImageView::SetTexture(std::string sFullPath)
{
	D3DXIMAGE_INFO stImageInfo;

	m_pTexture = g_pTextureManager->GetStdTexture(sFullPath, &stImageInfo);

	m_stSize.fWidth = stImageInfo.Width;
	m_stSize.fHeight = stImageInfo.Height;
}

void cMiniMapImageView::Render(LPD3DXSPRITE pSprite)
{
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_pTexture,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	pSprite->End();

	cMiniMapObject::Render(pSprite);
}
