#pragma once
#include <bitset>

#define KEYMAX 256
#define g_pKeyManager cKeyManager::GetInstance()

class cKeyManager
{
private:
	std::bitset<KEYMAX> _keyUp;
	std::bitset<KEYMAX> _keyDown;

public:
	cKeyManager();
	~cKeyManager();

	static cKeyManager* GetInstance()
	{
		static cKeyManager inst;
		return &inst;
	}

	HRESULT Setup(void);
	void release(void);

	bool isOnceKeyDown(int key);
	bool isOnceKeyUp(int key);
	bool isStayKeyDown(int key);
	bool isToggleKey(int key);

	std::bitset<KEYMAX> getKeyUp() { return _keyUp; }
	std::bitset<KEYMAX> getKeyDown() { return _keyDown; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }


};

