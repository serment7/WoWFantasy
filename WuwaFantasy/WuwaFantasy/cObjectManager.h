#pragma once

class cGameObject;

#define g_pObjectManager cObjectManager::GetInstance()

class cObjectManager
{
private:
	std::map<size_t, cGameObject*> m_mapObjectByID;
	std::map<size_t, std::vector<cGameObject*>> m_mapObjectByTag;

	size_t				m_unInstanceID = 1;

public:
	cObjectManager();
	~cObjectManager();

	static cObjectManager* GetInstance()
	{
		static cObjectManager instance;
		return &instance;
	}

	void AddObject(cGameObject* _object);
	void RemoveObject(cGameObject* _object);
	cGameObject*					FindObjectByID(const size_t& _id);
	std::vector<cGameObject*>&		FindObjectByTag(const size_t& _tag);
	void Destroy();
};