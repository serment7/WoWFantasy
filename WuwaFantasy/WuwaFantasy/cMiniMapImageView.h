#pragma once
#include "cMiniMapObject.h"

class cMiniMapImageView : public cMiniMapObject
{
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	cMiniMapImageView(void);
	virtual ~cMiniMapImageView(void);

	virtual void SetTexture(std::string sFullPath);

	virtual void Render(LPD3DXSPRITE pSprite) override;
};

