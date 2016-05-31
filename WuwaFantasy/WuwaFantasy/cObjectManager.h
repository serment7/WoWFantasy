#pragma once

class cObject;

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::map<size_t , cObject*> m_mapObjectByTag;
	std::map<size_t , cObject*> m_mapObjectByID;

public:
	cObjectManager();
	~cObjectManager();

	static cObjectManager* GetInstance()
	{
		static cObjectManager instance;
		return &instance;
	}

	void RegisterObject(cObject* _object);
	void UnregisterObject(cObject* _object);
	cObject* FindObjectByID(const size_t _id);
	cObject* FindObjectByTag(const size_t _tag);
	void Destroy();
};