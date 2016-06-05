#pragma once

class iObject;

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::set<iObject*> m_setObject;

public:
	cObjectManager();
	~cObjectManager();

	static cObjectManager* GetInstance()
	{
		static cObjectManager instance;
		return &instance;
	}

	void AddObject(iObject* _object);
	void RemoveObject(iObject* _object);
	void Destroy();
};