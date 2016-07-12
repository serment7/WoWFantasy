#pragma once
#include "cUIObject.h"

class cUIButton;

class iUIButtonDelegate
{
public:
	virtual void OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
public:
	cUIButton(void);
	virtual ~cUIButton(void);

protected:
	enum eButtonState
	{
		E_NORMAL,
		E_MOUSEOVER,
		E_SELECTED,
		E_COUNT
	};

	eButtonState		m_eState;
	LPDIRECT3DTEXTURE9	m_aTexture[E_COUNT];
	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate); 

public:
	virtual void SetTexture(std::string sNormal,
		std::string sMouseOver,
		std::string sSelected);

	virtual void Update() override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

