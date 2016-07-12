#include "StdAfx.h"
#include "cUIButton.h"


cUIButton::cUIButton(void)
	: m_eState(E_NORMAL)
	, m_pDelegate(NULL)
{
}


cUIButton::~cUIButton(void)
{
}

void cUIButton::SetTexture( std::string sNormal, std::string sMouseOver, std::string sSelected )
{
	D3DXIMAGE_INFO stImageInfo;
	m_aTexture[E_NORMAL] = g_pTextureManager->GetStdTexture(sNormal, &stImageInfo);
	m_aTexture[E_MOUSEOVER] = g_pTextureManager->GetStdTexture(sMouseOver, &stImageInfo);
	m_aTexture[E_SELECTED] = g_pTextureManager->GetStdTexture(sSelected, &stImageInfo);

	m_stSize.fWidth = stImageInfo.Width;
	m_stSize.fHeight = stImageInfo.Height;
}

void cUIButton::Update()
{
	POINT ptCurrMouse;
	GetCursorPos(&ptCurrMouse);
	ScreenToClient(g_hWnd, &ptCurrMouse);

	cUIObject::UpdateWorldTM();

	RECT rc;
	SetRect(&rc,
		m_matWorld._41,
		m_matWorld._42,
		m_matWorld._41 + m_stSize.fWidth,
		m_matWorld._42 + m_stSize.fHeight);

	if (PtInRect(&rc, ptCurrMouse))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eState == E_MOUSEOVER)
			{
				m_eState = E_SELECTED;
			}
		}
		else
		{
			if (m_eState == E_SELECTED)
			{
				// ¹öÆ° ´­·¶´Ù ¶À
				if (m_pDelegate)
				{
					m_pDelegate->OnClick(this);
				}

			}
			m_eState = E_MOUSEOVER;
		}
	}
	else
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
		}
		else
		{
			m_eState = E_NORMAL;
		}
	}

	cUIObject::UpdateChildren();
}

void cUIButton::Render( LPD3DXSPRITE pSprite )
{
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	pSprite->SetTransform(&m_matWorld);
	pSprite->Draw(m_aTexture[m_eState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));

	pSprite->End();

	cUIObject::Render(pSprite);
}
