#pragma once

class cGameObject;
class cIAction;

class cDelegate
{
public:
	virtual void OnActionDelegate(cIAction* _pSender) = 0;
};

class cIAction
{
private:
	cGameObject*	m_pOwner = nullptr;
	cDelegate*		m_pDelegate = nullptr;

	float			m_fPassedTime = 0.0f;
	float			m_fActionTime = 0.0f;
	bool			m_bAction;

protected:
	void			SetPassedTime(const float& _fPassedTime);
	void			SetActionTime(const float& _fActionTime);
	const float&	GetPassedTime() const;
	const float&	GetActionTime() const;

	void			SetAction(bool _bAction);

public:
	cIAction();
	virtual ~cIAction();
	
	void			SetOwner(cGameObject* _pOwner);
	cGameObject*	GetOwner();

	void			SetDelegate(cDelegate* _pDelegate);
	cDelegate*		GetDelegate();

	virtual void	Start() = 0;
	virtual void	Update() = 0;
	virtual void	Stop() = 0;
	bool			IsAction();
};

