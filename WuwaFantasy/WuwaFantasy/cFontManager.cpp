#include "StdAfx.h"
#include "cFontManager.h"


cFontManager::cFontManager(void)
{
}


cFontManager::~cFontManager(void)
{
}

LPD3DXFONT cFontManager::GetFont( eFontType e )
{
	if (m_mapFont.find(e) == m_mapFont.end())
	{
		if(e == E_FONT_QUEST)
		{
			D3DXFONT_DESC fd;
			ZeroMemory(&fd,sizeof(D3DXFONT_DESC));

			fd.Height			= 25;
			fd.Width			= 12;
			fd.Weight			= FW_NORMAL;
			fd.Italic			= false;
			fd.CharSet			= DEFAULT_CHARSET;
			fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily   = FF_DONTCARE;
			strcpy_s(fd.FaceName, "±Ã¼­Ã¼");

			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
		else if (e == E_FONT_NORMAL)
		{
			D3DXFONT_DESC fd;
			ZeroMemory(&fd,sizeof(D3DXFONT_DESC));

			fd.Height			= 25;
			fd.Width			= 12;
			fd.Weight			= FW_NORMAL;
			fd.Italic			= false;
			fd.CharSet			= DEFAULT_CHARSET;
			fd.OutputPrecision  = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily   = FF_DONTCARE;
			strcpy_s(fd.FaceName, "±Ã¼­Ã¼");

			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
		else if (e == E_FONT_NAME)
		{
			D3DXFONT_DESC fd;
			ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

			fd.Height = 10;
			fd.Width = 6;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "±Ã¼­Ã¼");

			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[e]);
		}
	}

	return m_mapFont[e];
}

void cFontManager::Destroy()
{
	for each(auto it in m_mapFont)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapFont.clear();
}
