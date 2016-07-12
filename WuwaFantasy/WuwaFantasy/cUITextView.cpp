#include "StdAfx.h"
#include "cUITextView.h"

cUITextView::cUITextView(void)
	: m_eFontType(cFontManager::E_FONT_NORMAL)
	, m_dwDrawTextFormat(DT_LEFT | DT_TOP | DT_WORDBREAK)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
}


cUITextView::~cUITextView(void)
{
}

void cUITextView::Render( LPD3DXSPRITE pSprite )
{
	LPD3DXFONT pFont = g_pFontManager->GetFont(m_eFontType);

	RECT rc;
	SetRect(&rc, 
		m_matWorld._41,
		m_matWorld._42,
		m_matWorld._41 + m_stSize.fWidth,
		m_matWorld._42 + m_stSize.fHeight);

	RECT client = g_pGameManager->GetClientSize();
	if (client.left < rc.left
		&& client.top < rc.top
		&& rc.right < client.right
		&& rc.bottom < client.bottom
		&&(m_matWorld._43<-9.0f
		||-1.0f<m_matWorld._43))
	{
		pFont->DrawTextA(NULL/*pSprite*/,
			m_sText.c_str(),
			m_sText.length(),
			&rc,
			m_dwDrawTextFormat,
			m_dwColor);
	}

	cUIObject::Render(pSprite);
}
