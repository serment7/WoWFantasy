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
	cStateMachine(cGameObject* _pOwner)
		:m_pOwner(_pOwner) {}
	virtual ~cStateMachine();

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

	bool MessageHandle(const ST_PACKET& msg) const
	{
		if (m_pCurrentState && m_pCurrentState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		if (m_pGlobalState && m_pGlobalState->OnMessage(m_pOwner, msg))
		{
			return true;
		}

		return false;
	}

	void  ChangeState(cIState* _pNewState)
	{
#ifdef _DEBUG
		assert(_pNewState && "ChangeState() received null ptr");
#endif
		m_pPreviousState = m_pCurrentState;
		m_pCurrentState->ExitState(m_pOwner);

		m_pCurrentState = _pNewState;
		m_pCurrentState->EnterState(m_pOwner);
	}

	void RevertState()
	{
		ChangeState(m_pPreviousState);
	}

	//returns true if the current state's type is equal to the type of the
	//class passed as a parameter. 
	//bool  isInState(const State<entity_type>& st)const
	//{
	//	if (typeid(*m_pCurrentState) == typeid(st)) return true;
	//	return false;
	//}

	cIState*  CurrentState()  const { return m_pCurrentState; }
	cIState*  GlobalState()   const { return m_pGlobalState; }
	cIState*  PreviousState() const { return m_pPreviousState; }

	////only ever used during debugging to grab the name of the current state
	//std::string         GetNameOfCurrentState()const
	//{
	//	std::string s(typeid(*m_pCurrentState).name());

	//	//remove the 'class ' part from the front of the string
	//	if (s.size() > 5)
	//	{
	//		s.erase(0, 6);
	//	}

	//	return s;
	//}
};

