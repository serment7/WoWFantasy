#pragma once

class cGameObject;
class cIAction;

class cActionDelegate
{
public:
	virtual void OnActionDelegate(cIAction* _pSender) = 0;
};

class cIAction
{
private:
	cGameObject*		m_pOwner = nullptr;
	cActionDelegate*	m_pDelegate = nullptr;

	float			m_fPassedTime = 0.0f;
	float			m_fActionTime = 0.0f;

public:
	cIAction();
	~cIAction();
	
	void SetOwner(cGameObject* _pOwner);
	void SetActionTime(const float& _fActionTime);
	void Start();
	void Update();
};

