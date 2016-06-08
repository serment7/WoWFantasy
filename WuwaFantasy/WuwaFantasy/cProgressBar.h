#pragma once

class cProgressBar
{
private:
	int m_nX;
	int m_nY;

public:
	cProgressBar();
	~cProgressBar();

	void Setup(int x, int y, int width, int height);
	void Setup(char* szUpImageFileName, char* szDownImageFileName, int x, int y, int width, int height);

	void Release();
	void Update();
	void Render();

	void SetGuage(float currentGuage, float maxGuage);

	void SetX(int x) { m_nX = x; }
	void SetY(int y) { m_nY = y; }
};