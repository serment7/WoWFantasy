#include "stdafx.h"
#include "cMiniMap.h"

cMiniMap::cMiniMap()
	: m_pSprite(NULL)
	, m_pMiniRoot(NULL)
{
}

cMiniMap::~cMiniMap()
{
	if (m_pMiniRoot)
	{
		m_pMiniRoot->Destroy();
		m_pMiniRoot = NULL;
	}
}

void cMiniMap::EnterScene()
{

	Minimap = new cMiniMapImageView;
	g_pSpriteManager->GetTexture(std::string("./Resource/MiniMap/Minimap.png"),image_info);
	MiniMapX = image_info.Width;
	MiniMapY = image_info.Height;
	Minimap->SetTexture("./Resource/MiniMap/Minimap.png");
	Minimap->SetPosition(D3DXVECTOR3(800, 0, 0));
	m_pMiniRoot = Minimap;

	MinimapPlayer = NULL;
	MinimapPlayer = new cMiniMapImageView;
	MinimapPlayer->SetTexture("./Resource/MiniMap/PlayerMap.png");
	m_pMiniRoot->AddChild(MinimapPlayer);
	
	MinimapNpc = NULL;
	MinimapNpc = new cMiniMapImageView;
	MinimapNpc->SetTexture("./Resource/MiniMap/NpcMap.png");
	m_pMiniRoot->AddChild(MinimapNpc);
	
	MinimapEnemy = NULL;
	MinimapEnemy = new cMiniMapImageView;
	MinimapEnemy->SetTexture("./Resource/MiniMap/EnemyMap.png");
	m_pMiniRoot->AddChild(MinimapEnemy);

	m_pSprite = g_pSpriteManager->GetSprite();
}

void cMiniMap::Update()
{
	if (Minimap)
	{
		Minimap->Update();
	}

}
void cMiniMap::Render()
{
	if (Minimap)
	{
		Minimap->Render(m_pSprite);
	}

	for (size_t i = 0; i < objects.size(); ++i)
	{
		D3DXVECTOR3 drawPos = (D3DXVECTOR3(objects[i]->GetVPos().x, objects[i]->GetVPos().z, 0));
		drawPos.x *= (MiniMapX/512);
		drawPos.y *= (MiniMapY/512);

		if (objects[i]->GetTag() == g_pGameManager->FindObjectType("player"))
		{
			MinimapPlayer->SetPosition(drawPos);
			MinimapPlayer->Update();
			MinimapPlayer->Render(m_pSprite);
		}
		else if (objects[i]->GetTag() == g_pGameManager->FindObjectType("combatnpc"))
		{
			MinimapNpc->SetPosition(drawPos);
			MinimapNpc->Update();
			MinimapNpc->Render(m_pSprite);
		}
		else if (objects[i]->GetTag() == g_pGameManager->FindObjectType("monster"))
		{
			MinimapEnemy->SetPosition(drawPos);
			MinimapEnemy->Update();
			MinimapEnemy->Render(m_pSprite);
		}
	}	

}
void cMiniMap::ExitScene()
{

}
void cMiniMap::SetPos(cGameObject* _pObject)
{
	objects.push_back(_pObject);
}