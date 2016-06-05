#pragma once

class cObject;

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::map<size_t, cObject*> m_mapObjectByID;
	std::map<size_t, std::vector<cObject*>> m_mapObjectByTag;

public:
	cObjectManager();
	~cObjectManager();

	static cObjectManager* GetInstance()
	{
		static cObjectManager instance;
		return &instance;
	}

	void AddObject(cObject* _object);
	void RemoveObject(cObject* _object);
	cObject*					FindObjectByID(const size_t& _id);
	std::vector<cObject*>&		FindObjectByTag(const size_t& _tag);
	void Destroy();
};