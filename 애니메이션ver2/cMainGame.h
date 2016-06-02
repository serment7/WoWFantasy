#pragma once

class cCamera;
class cGrid;
class cSkinnedMesh;
class cWeaponSkinnedMesh;

class cMainGame
{
private:
	cCamera*				m_pCamera;
	cGrid*					m_pGrid;
	cSkinnedMesh*			m_pSkinnedMesh;
	cWeaponSkinnedMesh*		m_pWeapon;

public:
	cMainGame(void);
	~cMainGame(void);

	void Setup();
	void Update();
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

