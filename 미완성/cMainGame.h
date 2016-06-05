
#pragma once

class cGrid;
class cCamera;

class cMainGame 
{
private:
	cGrid*									grid;
	cCamera*								camera;

public:
	cMainGame();
	~cMainGame();

	void Setup();
	void Update();
	void Render();

	void CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
