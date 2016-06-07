
#pragma once
#include "cObject.h"
#include "cStatus.h"
#include "cSkinnedMesh.h"
#include "cWeaponSkinnedMesh.h"

const std::string MODEL_PATH = "./Resource/Model/";

class cCondition;
class cAction;

class cGameObject : public cObject
{
public:
	cStatus						m_pStatus;
	BOOL						m_isObject;

	cSkinnedMesh*				m_chrSkinnedMesh = nullptr;
	cWeaponSkinnedMesh*			m_objSkinnedMesh = nullptr;
	LPD3DXMESH					m_sphere = nullptr;


	cStateMachine*				m_pStateMachine=nullptr;
	std::list<cCondition*>		m_listCondition;

	size_t						m_unID = -1;
	size_t						m_unTag = -1;

	cAction*					m_pAction;

public:
	cGameObject();
	virtual ~cGameObject();

	virtual void		Update();
	virtual void		Render();

	void SetID(const size_t& _id);
	void SetTag(const size_t& _tag);
	const size_t& GetID();
	const size_t& GetTag();

	cStatus&			GetStatus();
	cSkinnedMesh*		GetSkinnedMesh() { return m_chrSkinnedMesh; };
	void				SetStateMachine(cStateMachine* _pStateMachine);
	cStateMachine*		GetStateMachine();
	LPD3DXMESH			GetBound();

	void				AddCondition(cCondition* _pCondition);
	void				OnMessage(const ST_PACKET& _packet);

	cAction*			GetAction();
};