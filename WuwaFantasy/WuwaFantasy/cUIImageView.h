#pragma once
#include "cUIObject.h"

class cUIImageView : public cUIObject
{
private:
	LPDIRECT3DTEXTURE9 m_pTexture;

public:
	cUIImageView(void);
	virtual ~cUIImageView(void);

	virtual void SetTexture(std::string sFullPath);

	virtual void Render(LPD3DXSPRITE pSprite) override;
};

