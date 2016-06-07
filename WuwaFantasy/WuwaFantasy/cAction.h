#pragma once

class cGameObject;
class cAction;

class cActionDelegate
{
public:
	virtual void OnActionDelegate(cAction* _pSender) = 0;
};

class cAction
{
private:
	cGameObject*			m_pOwner = nullptr;
	cActionDelegate*		m_pDelegate = nullptr;

	float					m_fPassedTime = 0.0f;
	float					m_fActionTime = 0.0f;
	bool					m_bAction;

	D3DXVECTOR3				m_vFrom = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3				m_vTo = D3DXVECTOR3(0, 0, 0);
	cGameObject*			pTarget = nullptr;

public:
	cAction(cGameObject* _pOwner);
	~cAction();

	cGameObject*			GetOwner();
	void					Start();
	void					Stop();
	void					SetDelegate(cActionDelegate* _pDelegate);

	void					ReadyMoveTo(const D3DXVECTOR3& _vFrom, const D3DXVECTOR3& _vTo);
	void					MoveTo();
	void					ReadyHeadTo(const D3DXVECTOR3& _vFrom, const D3DXVECTOR3& _vTo);
	void					HeadTo();
};

