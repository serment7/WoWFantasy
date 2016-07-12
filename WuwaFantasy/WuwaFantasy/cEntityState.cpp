#include "stdafx.h"
#include "cEntityState.h"
#include "cUIObject.h"
#include "cUITextView.h"
#include "cGameObject.h"
#include "cSkill.h"

cEntityState::cEntityState()
{
}


cEntityState::~cEntityState()
{
	m_pUIRoot->Destroy();
}

void cEntityState::EnterState(cGameObject * _entity)
{
	head.y=_entity->GetBoundSphere().fRadius;
	m_pNameText = new cUITextView;
	m_pNameText->SetText(_entity->GetName());
	m_pNameText->SetFontType(cFontManager::E_FONT_NAME);
	m_nTextHeight = 20;
	m_nTextWidth = 120;
	m_pNameText->SetSize(ST_SIZE(m_nTextWidth, m_nTextHeight));

	m_pNameText->SetTextColor(D3DCOLOR_XRGB(255, 255, 0));
	m_pNameText->SetDrawTextFormat(DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	m_pNameText->SetTag(E_TEXTVIEW);
	m_pUIRoot = m_pNameText;
}

void cEntityState::Execute(cGameObject * _entity)
{
	if (m_pUIRoot)
	{
		head = _entity->GetVPos();
		head.y += _entity->GetBoundSphere().fRadius;
		viewMat = g_pGameManager->GetViewMat();
		D3DXVec3TransformCoord(&head, &head, &(viewMat));
		projMat = g_pGameManager->GetProjMat();
		D3DXVec3TransformCoord(&head, &head, &(projMat));
		portMat = g_pGameManager->GetPortMat();
		D3DXVec3TransformCoord(&head, &head, &(portMat));

		const RECT& rect = g_pGameManager->GetClientSize();

		m_pNameText->SetPosition(head + D3DXVECTOR3(m_nTextWidth, 0, m_nTextHeight)*-0.5f);
		m_pUIRoot->Update();
	}
}
