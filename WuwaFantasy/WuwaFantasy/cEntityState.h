#pragma once
#include "cIState.h"


class cStatus;
class cSkill;
class cUIObject;
class cUITextView;

#define BASE_ATTACK VK_RBUTTON

class cEntityState :
	public cIState
{
protected:
	cGameObject*				m_pOwner=nullptr;
	size_t						m_entityID = MAXSIZE_T;
	cIState*					m_pState = nullptr;
	cStatus*					m_pStatus = nullptr;

	cGameObject*				m_pTarget=nullptr;
	bool						m_bCombat = false;
	bool						m_bLive = true;

	std::map<char, cSkill*>		m_mapSkill;
	cSkill*						m_pCurSkill = nullptr;

	D3DXVECTOR3					head = D3DXVECTOR3(0, 0, 0);
	cUIObject*					m_pUIRoot=nullptr;
	cUITextView*				m_pNameText = nullptr;

	int						m_nTextWidth = 120, m_nTextHeight = 20;

	D3DXMATRIXA16 viewMat, projMat;
	D3DXMATRIXA16 portMat;
	D3DVIEWPORT9 viewport;

public:
	cEntityState();
	virtual ~cEntityState();
	
	virtual void		EnterState(cGameObject* _entity);
	virtual void		Execute(cGameObject* _entity);
};

