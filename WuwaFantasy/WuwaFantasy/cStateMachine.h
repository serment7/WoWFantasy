#pragma once
#include"cIState.h"

class cGameObject;

class cStateMachine
{
protected:
	cGameObject*			m_pOwner = nullptr;
	cIState*				m_pPreviousState = nullptr;
	cIState*				m_pCurrentState = nullptr;
	cIState*				m_pGlobalState = nullptr;

public:
	cStateMachine() {};
	virtual ~cStateMachine();

	virtual void		Setup() {};

	void SetCurrentState(cIState* _currentState)
	{
		m_pCurrentState = _currentState;
	}
	void SetPreviousState(cIState* _privioustState)
	{
		m_pPreviousState = _privioustState;
	}
	void SetGlobalState(cIState* _globalState)
	{
		m_pGlobalState = _globalState;
	}

	void Update()
	{
		if (m_pGlobalState)
			m_pGlobalState->Execute(m_pOwner);
		
		if (m_pCurrentState)
			m_pCurrentState->Execute(m_pOwner);
	}

	virtual bool MessageHandle(const ST_PACKET& msg);

	void  ChangeState(cIState* _pNewState);

	void RevertState();

	cIState*  CurrentState()  const { return m_pCurrentState; }
	cIState*  GlobalState()   const { return m_pGlobalState; }
	cIState*  PreviousState() const { return m_pPreviousState; }
};

