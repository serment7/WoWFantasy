
#include "stdafx.h"
#include "cSceneManager.h"

cSceneManager::cSceneManager()
:	pGameScene(NULL)
,	pLoadingScene(NULL)
,	pReadyScene(NULL)
{

}

cSceneManager::~cSceneManager()
{

}

void cSceneManager::Release()
{
	for (size_t viSceneList = 0; viSceneList<vSceneList.size(); ++viSceneList)
	{
		if (vSceneList[viSceneList].second != NULL)
		{
			if (vSceneList[viSceneList].second == pGameScene) 
			{
				vSceneList[viSceneList].second->ExitScene();
			}
			SAFE_DELETE(vSceneList[viSceneList].second);
			
		}
	}

	vSceneList.clear();
}

void cSceneManager::Update()
{
	if(pGameScene) pGameScene->Update();
}

void cSceneManager::Render()
{
	if(pGameScene) pGameScene->Render();
}

//일반 씬 추가
cIScene* cSceneManager::AddScene(char* sceneName, cIScene* scene)
{
	std::string pSceneName(sceneName);

	if(scene != NULL)
	{
		vSceneList.push_back(std::make_pair(pSceneName, scene));
	}

	return scene;
}

//로딩 씬 추가
cIScene* cSceneManager::AddLoadingScene(char* loadingSceneName, cIScene* scene)
{
	/*
	std::string pSceneName(loadingSceneName);

	if(scene != NULL)
	{
		mSceneList.insert(std::make_pair(pSceneName, scene));
	}

	return scene;
	*/
	return NULL;
}

//씬 바꾸기(EnterScene)
bool cSceneManager::ChangeScene(char* sceneName)
{
	std::string pSceneName(sceneName);

	for(viSceneList = vSceneList.begin(); viSceneList != vSceneList.end(); ++viSceneList)
	{
		if(viSceneList->first == sceneName)
		{
			//씬이 아니라면 바꿔주고 끝낸다.
			if(viSceneList->second != pGameScene)
			{
				if(pGameScene) pGameScene->ExitScene();
				pGameScene = viSceneList->second;
			}
			return true;
		}
	}

	//위 루프를 빠져나왔으면 못찾았다란 소리니까

	return false;

}

bool cSceneManager::ChangeScene(char* sceneName, char* loadingSceneName)
{
	/*
	std::string pSceneName(sceneName);
	std::string pLoadingSceneName(loadingSceneName);

	std::map<std::string, cInGameScene*>::iterator mifindScene;
	mifindScene = mSceneList.find(pSceneName);

	//씬을 못찾았을 경우
	if(mifindScene == mSceneList.end()) return false;

	//이미 그 씬이라면
	if (mifindScene->second == pGameScene) return true;

	//mapSceneIter findLoadingScene = mSceneList.find(pLoadingSceneName);

	//둘 다 아니라면 바꿔준다
	if (pGameScene) 
	{
		pGameScene->ExitScene();
	}

	pGameScene = mifindScene->second;
	*/
	return true;
}
