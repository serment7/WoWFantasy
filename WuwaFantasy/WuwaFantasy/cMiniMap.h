#pragma once
#include "cInGameScene.h"
#include "cMiniMapObject.h"
#include "cMiniMapImageView.h"
class cMiniMapPoint;
class cGameObject;

class cMiniMap : public cMiniMapObject
{
private:	
	cMiniMapPoint*	     m_pMiniMapPoint;
	cMiniMapObject*		 m_pMiniRoot;

	cMiniMapImageView*	 Minimap;
	cMiniMapImageView*	 MinimapPlayer;
	cMiniMapImageView*	 MinimapNpc;
	cMiniMapImageView*	 MinimapEnemy;

	D3DXIMAGE_INFO		 image_info;

	float MiniMapX, MiniMapY;

	std::vector<cGameObject*> objects;

protected:
	//std::vector<cMiniMapImageView*> MinimapNpc;
	//std::vector<cMiniMapImageView*> MinimapEnemy;

	D3DXMATRIXA16			m_matWorld;
	LPDIRECT3DTEXTURE9		m_pTexture;
	LPD3DXSPRITE			m_pSprite;
	SYNTHESIZE(ST_SIZE, m_stSize, Size);

public:
	cMiniMap();
	~cMiniMap();

	virtual void	EnterScene();
	virtual void	Update();
	virtual void	Render();
	virtual void	ExitScene();
	virtual void	SetPos(cGameObject* _pObject);

};

