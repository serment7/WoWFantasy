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

protected:
	void SetPassedTime(const float& _fPassedTime);
	void SetActionTime(const float& _fActionTime);
	const float& GetPassedTime() const;
	const float& GetActionTime() const;

public:
	cIAction();
	virtual ~cIAction();
	
	void SetOwner(cGameObject* _pOwner);
	cGameObject* GetOwner();

	void SetDelegate(cActionDelegate* _pDelegate);

	virtual void Start() = 0;
	virtual void Update() = 0;
};

