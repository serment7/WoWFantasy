#include "stdafx.h"
#include "cUIClass.h"
#include "cSkill.h"

cUIClass::cUIClass()
	: m_pFont(NULL)
	, m_pUIRoot(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIClass::~cUIClass()
{
	SAFE_RELEASE(m_pFont);
	if (m_pUIRoot)
	{
		m_pUIRoot->Destroy();
		m_pUIRoot = NULL;
	}
	if (m_pNumHud)
	{
		m_pNumHud->Destroy();
		m_pNumHud = NULL;
	}
}
void cUIClass::EnterScene()
{
	m_playerID = g_pGameManager->GetPlayerID();

	cUIImageView* pImageView = new cUIImageView;
	pImageView->SetTexture("./Resource/UI/HUD.png");
	pImageView->SetPosition(D3DXVECTOR3(140, 650, 0));
	pImageView->SetDepth(0.7f);
	m_pUIRoot = pImageView;

	cUIImageView* HUNnum = new cUIImageView;
	HUNnum->SetTexture("./Resource/UI/HUDNum.png");
	HUNnum->SetPosition(m_pUIRoot->GetPosition());
	HUNnum->SetDepth(0.0f);
	m_pNumHud = HUNnum;
}

void cUIClass::Update()
{
	if (!m_mapSkill.empty())
	{
		for (auto iter = m_mapSkill.begin(); iter != m_mapSkill.end(); ++iter)
		{
			if (iter->second->IsCoolDown())
			{
				m_mapSkillProgress[iter->first]->SetGuage(iter->second->GetPassedCoolTime(),iter->second->GetCoolDownTime());
			}
			else
			{
				m_mapSkillProgress[iter->first]->SetGuage(1.0f,1.0f);
			}
		}
	}
	if (m_pUIRoot)
	{
		m_pUIRoot->Update();
		m_pNumHud->Update();
	}
}

void cUIClass::Render()
{
	g_pSpriteManager->SetTransform(m_matWorld);
	if (m_pUIRoot) {
		m_pUIRoot->Render(g_pSpriteManager->GetSprite());
		m_pNumHud->Render(g_pSpriteManager->GetSprite());
	}
		
}

void cUIClass::ExitScene()
{

}

void cUIClass::OnClick(cUIProgressButton* pSender)
{
	for (char index = KeyEnum::SKILL0; index < KeyEnum::END; ++index)
	{
		if (pSender->GetTag() == index)
		{
			packet_useskill = new Packet_UseSkill(index);
			g_pMessageDispatcher->Dispatch(0, m_playerID, 0.0f, Msg_UseSkill, packet_useskill);
			break;
		}
	}
}

void cUIClass::SetSkill(const char & _key, cSkill * _pSkill)
{
	if (KeyEnum::SKILL0 <= _key&&_key < KeyEnum::END)
	{
		cUIProgressButton* pButton=nullptr;
		if (m_mapSkill.find(_key) != m_mapSkill.end())
			pButton = m_mapSkillProgress[_key];
		else
		{
			pButton = new cUIProgressButton;
			m_pUIRoot->AddChild(pButton);
		}
		pButton->Setup(_pSkill->GetPath().substr()+".png", _pSkill->GetPath().substr() + "Äð.png", 0, 0, 72, 62);
		if (_key!=KeyEnum::SKILL0)
			pButton->SetPosition(D3DXVECTOR3(4 + (76 * (_key - KeyEnum::SKILL1)), 4, 0));
		else
			pButton->SetPosition(D3DXVECTOR3(4 + (76 * (KeyEnum::END - KeyEnum::SKILL1)), 4, 0));
		
		pButton->SetTag(_key);
		pButton->SetDelegate(this);		
		m_mapSkillProgress[_key] = pButton;
		m_mapSkill[_key] = _pSkill;
	}
}
