#include "stdafx.h"
#include "cUserHUD.h"
#include "cUIClass.h"
#include "cProgressBar.h"
#include "cMiniMap.h"

cUserHUD::cUserHUD()
{
	m_pMinimap = new cMiniMap;
	m_pMinimap->EnterScene();
	m_font = g_pFontManager->GetFont(g_pFontManager->E_FONT_NAME);
}


cUserHUD::~cUserHUD()
{
}

void cUserHUD::EnterScene()
{
	m_pUIClass = new cUIClass();
	m_pUIClass->EnterScene();

	m_pUserHPBar = new cProgressBar;
	m_pUserHPBar->Setup("./Resource/UI/HPbar2.png", "./Resource/UI/ProgressBar2.png", 10, 20, 300, 19);

	m_pTargetHPBar = new cProgressBar;
	m_pTargetHPBar->Setup("./Resource/UI/EnemyHPbar.png", "./Resource/UI/ProgressBar2.png", 430, 20, 300, 19);

	m_pUserMPBar = new cProgressBar;
	m_pUserMPBar->Setup("./Resource/UI/MPbar2.png", "./Resource/UI/MpProgressBar2.png", 10, 39, 300, 9);

	m_pUser = g_pObjectManager->FindObjectByID(g_pGameManager->GetPlayerID());
}

void cUserHUD::ExitScene()
{
	SAFE_RELEASE(m_pUserHPBar);
	SAFE_RELEASE(m_pUserMPBar);

	SAFE_RELEASE(m_pTargetHPBar);
	SAFE_RELEASE(m_pMinimap);

	for (auto iter = m_mapPartyHPBar.begin(); iter != m_mapPartyHPBar.end(); ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapPartyHPBar.clear();
	for (auto iter = m_mapPartyMPBar.begin(); iter != m_mapPartyMPBar.end(); ++iter)
	{
		SAFE_RELEASE(iter->second);
	}
	m_mapPartyMPBar.clear();
	m_pUIClass->ExitScene();
	SAFE_DELETE(m_pUIClass);
}

void cUserHUD::Update()
{
	cStatus status = m_pUser->GetStatus();
	m_pUserHPBar->SetGuage(status.GetCurrentHP(),status.GetMaxHP());
	m_pUserMPBar->SetGuage(status.GetCurrentMP(), status.GetMaxMP());

	if (m_pTarget && m_pTarget->IsShow())
	{
		status = m_pTarget->GetStatus();
		m_pTargetHPBar->SetGuage(status.GetCurrentHP(),status.GetMaxHP());
		m_pTargetHPBar->Update();
	}
	else
		m_pTarget = nullptr;

	for (size_t index = 0; index < m_vecObjects.size(); ++index)
	{
		status = m_vecObjects[index]->GetStatus();
		m_mapPartyHPBar[m_vecObjects[index]->GetID()]->SetGuage(status.GetCurrentHP(),status.GetMaxHP());
		m_mapPartyMPBar[m_vecObjects[index]->GetID()]->SetGuage(status.GetCurrentMP(), status.GetMaxMP());
	}


	m_pUserHPBar->Update();
	m_pUserMPBar->Update();
	for (auto iter = m_mapPartyHPBar.begin(); iter != m_mapPartyHPBar.end(); ++iter)
	{
		iter->second->Update();
	}
	for (auto iter = m_mapPartyMPBar.begin(); iter != m_mapPartyMPBar.end(); ++iter)
	{
		iter->second->Update();
	}
	m_pMinimap->Update();
	m_pUIClass->Update();
}

void cUserHUD::Render()
{
	m_pUserHPBar->Render();
	m_pUserMPBar->Render();
	if (m_pTarget && m_pTarget->IsShow())
		m_pTargetHPBar->Render();
	
	RECT rect;
	D3DXMATRIXA16 mat;
	D3DXMatrixIdentity(&mat);
	g_pSpriteManager->BeginSprite();
	g_pSpriteManager->SetTransform(mat);
	for (size_t index = 0; index < m_vecObjects.size(); ++index)
	{
		int offset = (index * 50);
		rect.left = 10;
		rect.top = 60 + offset;
		rect.right = 100;
		rect.bottom = 70 + offset;

		std::string name(m_vecObjects[index]->GetName().substr());
		m_font->DrawTextA(g_pSpriteManager->GetSprite(), name.c_str(), name.length(),&rect, DT_LEFT | DT_TOP | DT_WORDBREAK,D3DCOLOR_XRGB(255,255,255));
	}
	g_pSpriteManager->EndSprite();
	for (auto iter = m_mapPartyHPBar.begin(); iter != m_mapPartyHPBar.end(); ++iter)
	{
		iter->second->Render();
	}
	for (auto iter = m_mapPartyMPBar.begin(); iter != m_mapPartyMPBar.end(); ++iter)
	{
		iter->second->Render();
	}
	m_pUIClass->Render();
	m_pMinimap->Render();
}

void cUserHUD::AddParty(cGameObject * _pParty)
{
	cProgressBar* pHPProgressBar=new cProgressBar;
	pHPProgressBar->Setup("./Resource/UI/HPbar.png", "./Resource/UI/ProgressBar1.png", 10, 70+m_vecObjects.size()*50, 150, 19);
	m_mapPartyHPBar.insert(std::pair<size_t,cProgressBar*>(_pParty->GetID(),pHPProgressBar));

	cProgressBar* pMPProgressBar = new cProgressBar;
	pMPProgressBar->Setup("./Resource/UI/MPbar.png", "./Resource/UI/MpProgressBar1.png", 10, 89+ m_vecObjects.size() * 50, 150, 9);
	m_mapPartyMPBar.insert(std::pair<size_t, cProgressBar*>(_pParty->GetID(), pMPProgressBar));

	m_vecObjects.push_back(_pParty);
}

void cUserHUD::SetSkill(const char & _key, cSkill * _pSkill)
{
	m_pUIClass->SetSkill(_key,_pSkill);
}

void cUserHUD::SetTarget(cGameObject * _pTarget)
{
	m_pTarget = _pTarget;
}

void cUserHUD::LostTarget()
{
	m_pTarget = nullptr;
}

void cUserHUD::RegisterObjectOnMinimap(cGameObject * _pObject)
{
	m_pMinimap->SetPos(_pObject);
}
