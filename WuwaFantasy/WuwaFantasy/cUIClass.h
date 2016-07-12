#pragma once
#include "cInGameScene.h"
#include "cUIButton.h"
#include "cUIObject.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cUIProgressButton.h"

class cSkill;

class cUIClass : 
	public iUIProgressButtonDelegate
{
private:
	cUIObject*							m_pUIRoot;
	cUIObject*							m_pNumHud = nullptr;
	std::map<char, cSkill*>				m_mapSkill;
	std::map<char, cUIProgressButton* > m_mapSkillProgress;
	Packet_UseSkill*					packet_useskill=nullptr;
	LPD3DXFONT							m_pFont;
	D3DXMATRIXA16						m_matWorld;
	size_t								m_playerID=MAXSIZE_T;
public:	
	cUIClass();
	~cUIClass();

	virtual void	Update();
	virtual void	Render();
	virtual void	EnterScene();
	virtual void	ExitScene();
	virtual void	OnClick(cUIProgressButton* pSender) override;
	void			SetSkill(const char& _key,cSkill* _pSkill);
};

