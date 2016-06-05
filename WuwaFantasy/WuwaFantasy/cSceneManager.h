
#pragma once
#include "cIScene.h"

class cSceneManager  
{
public:
	std::vector< std::pair<std::string, cIScene*> > vSceneList;
	std::vector< std::pair<std::string, cIScene*> >::iterator viSceneList;

private:
	cIScene*			pGameScene;				//���� ��
	cIScene*			pLoadingScene;			//�ε� ��
	cIScene*			pReadyScene;			//�غ�� ��
	
	DWORD					nLoadThreadID;

public:
	cSceneManager();
	~cSceneManager();

	void Release();
	void Update();
	void Render();

	//�Ϲ� �� �߰�
	cIScene* AddScene(char* sceneName, cIScene* scene);

	//�ε� �� �߰�
	cIScene* AddLoadingScene(char* loadingSceneName, cIScene* scene);

	//�� �ٲٱ�
	bool ChangeScene(char* sceneName);
	bool ChangeScene(char* sceneName, char* loadingSceneName);

	//�ε� �����带 ���� ������ �Լ�
	//friend DWORD CALLBACK loadingThread(LPVOID prc);
	cIScene* GetGameScene();
};
