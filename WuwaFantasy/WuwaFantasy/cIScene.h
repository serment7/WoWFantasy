#pragma once
class cIScene
{
private:
	
public:
	cIScene();
	virtual ~cIScene();

	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void EnterScene() = 0;
	virtual void ExitScene() = 0;
	virtual void ChangeScene(cIScene*) = 0;
	virtual void MessageHandling(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) = 0;
};
