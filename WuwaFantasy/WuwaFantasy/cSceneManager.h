
#pragma once
#include "cIScene.h"

class cSceneManager  
{
public:
	std::vector< std::pair<std::string, cIScene*> > vSceneList;
	std::vector< std::pair<std::string, cIScene*> >::iterator viSceneList;

private:
	cIScene*			pGameScene;				//게임 씬
	cIScene*			pLoadingScene;			//로딩 씬
	cIScene*			pReadyScene;			//준비된 씬
	
	DWORD					nLoadThreadID;

public:
	cSceneManager();
	~cSceneManager();

	void Release();
	void Update();
	void Render();

	//일반 씬 추가
	cIScene* AddScene(char* sceneName, cIScene* scene);

	//로딩 씬 추가
	cIScene* AddLoadingScene(char* loadingSceneName, cIScene* scene);

	//씬 바꾸기
	bool ChangeScene(char* sceneName);
	bool ChangeScene(char* sceneName, char* loadingSceneName);

	//로딩 쓰레드를 위한 쓰레드 함수
	//friend DWORD CALLBACK loadingThread(LPVOID prc);
	cIScene* GetGameScene();
};
