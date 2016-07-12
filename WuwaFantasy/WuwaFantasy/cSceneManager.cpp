
#include "stdafx.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
{

}

cSceneManager::~cSceneManager()
{
	Release();
}

cIScene* cSceneManager::m_pGameScene = NULL;
cIScene* cSceneManager::m_pLoadingScene = NULL;
cIScene* cSceneManager::m_pReadyScene = NULL;

mSceneList cSceneManager::m_mapSceneList;
miSceneList	cSceneManager::m_mapiterSceneList;

void cSceneManager::Release()
{
	miSceneList miSceneRelease = m_mapSceneList.begin();
	for (; miSceneRelease != m_mapSceneList.end();)
	{
		if (miSceneRelease->second != nullptr)
		{
			if(miSceneRelease->second == m_pGameScene) 
				miSceneRelease->second->ExitScene();
			SAFE_DELETE(miSceneRelease->second);
			miSceneRelease = m_mapSceneList.erase(miSceneRelease);
		}
		else
		{
			++miSceneRelease;
		}
	}

	m_mapSceneList.clear();
}

void cSceneManager::Update()
{
	if(m_pGameScene) m_pGameScene->Update();
}

void cSceneManager::Render()
{
	if(m_pGameScene) m_pGameScene->Render();
}

cIScene* cSceneManager::AddScene(std::string szSceneName, cIScene* nScene)
{
	//if (nScene == nullptr) return nullptr;

	m_mapSceneList.insert(std::make_pair(szSceneName, nScene));

	return nScene;
}

bool cSceneManager::ChangeScene(std::string szSceneName)
{
	miSceneList findScene = m_mapSceneList.find(szSceneName);
	if (findScene == m_mapSceneList.end()) return false;
	if (findScene->second == m_pGameScene) return true;

	if (m_pGameScene) m_pGameScene->ExitScene();
	m_pGameScene = findScene->second;
	m_pGameScene->EnterScene();

	return true;
}

bool cSceneManager::ChangeScene(char* szSceneName, char* szLoadingSceneName)
{
	miSceneList findMainGameScene = m_mapSceneList.find(szSceneName);
	if (findMainGameScene == m_mapSceneList.end()) return false;

	if (m_pGameScene) m_pGameScene->ExitScene();
	m_pGameScene = findMainGameScene->second;

	miSceneList findLoadingGameScene = m_mapSceneList.find(szLoadingSceneName);
	if (findLoadingGameScene == m_mapSceneList.end()) return false;

	if (m_pLoadingScene) m_pLoadingScene->ExitScene();
	m_pLoadingScene = findLoadingGameScene->second;

	m_pReadyScene = m_pGameScene;
	m_pGameScene = m_pLoadingScene;

	return true;
}

cIScene* cSceneManager::GetGameScene()
{
	return m_pGameScene;
}

cIScene* cSceneManager::GetLoadingScene()
{
	return m_pLoadingScene;
}

cIScene * cSceneManager::GetReadyScene()
{
	return m_pReadyScene;
}
