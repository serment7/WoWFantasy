
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

//�Ϲ� �� �߰�
cIScene* cSceneManager::AddScene(char* sceneName, cIScene* scene)
{
	std::string pSceneName(sceneName);

	if(scene != NULL)
	{
		vSceneList.push_back(std::make_pair(pSceneName, scene));
	}

	return scene;
}

//�ε� �� �߰�
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

//�� �ٲٱ�(EnterScene)
bool cSceneManager::ChangeScene(char* sceneName)
{
	std::string pSceneName(sceneName);

	for(viSceneList = vSceneList.begin(); viSceneList != vSceneList.end(); ++viSceneList)
	{
		if(viSceneList->first == sceneName)
		{
			//���� �ƴ϶�� �ٲ��ְ� ������.
			if(viSceneList->second != pGameScene)
			{
				if(pGameScene) pGameScene->ExitScene();
				pGameScene = viSceneList->second;
			}
			return true;
		}
	}

	//�� ������ ������������ ��ã�Ҵٶ� �Ҹ��ϱ�

	return false;

}

bool cSceneManager::ChangeScene(char* sceneName, char* loadingSceneName)
{
	/*
	std::string pSceneName(sceneName);
	std::string pLoadingSceneName(loadingSceneName);

	std::map<std::string, cInGameScene*>::iterator mifindScene;
	mifindScene = mSceneList.find(pSceneName);

	//���� ��ã���� ���
	if(mifindScene == mSceneList.end()) return false;

	//�̹� �� ���̶��
	if (mifindScene->second == pGameScene) return true;

	//mapSceneIter findLoadingScene = mSceneList.find(pLoadingSceneName);

	//�� �� �ƴ϶�� �ٲ��ش�
	if (pGameScene) 
	{
		pGameScene->ExitScene();
	}

	pGameScene = mifindScene->second;
	*/
	return true;
}
