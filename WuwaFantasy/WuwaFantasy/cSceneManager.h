
#pragma once
#define g_pSceneManager cSceneManager::GetInstance() 

#include "cIScene.h"

typedef std::map<std::string, cIScene*> mSceneList;
typedef std::map<std::string, cIScene*>::iterator miSceneList;

class cSceneManager  
{
private:

	static mSceneList		m_mapSceneList;
	static miSceneList		m_mapiterSceneList;

	static cIScene*			m_pGameScene;
	static cIScene*			m_pLoadingScene;
	static cIScene*			m_pReadyScene;
	
	DWORD				m_nLoadThreadID;
	BOOL				m_isLoadingScene;

public:
	cSceneManager();
	~cSceneManager();

	static cSceneManager* GetInstance()
	{
		static cSceneManager* mag;
		return mag;
	}

	void Release();
	void Update();
	void Render();

	cIScene* AddScene(std::string szSceneName, cIScene* nScene);

	bool ChangeScene(std::string szSceneName);
	bool ChangeScene(char* szSceneName, char* szLoadingSceneName);

	cIScene* GetGameScene();
	cIScene* GetLoadingScene();
	cIScene* GetReadyScene();

	void SetGameScene(cIScene* gameScene) { m_pGameScene = gameScene; }
	void SetReadyScene(cIScene* readyScene) { m_pReadyScene = readyScene; }
	void SetLoadingScene(cIScene* loadingScene) { m_pLoadingScene = loadingScene; }
};
