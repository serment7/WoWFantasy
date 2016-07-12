#pragma once
#include "Triangle.h"

class cSkyBox
{
public:
	cSkyBox();
	~cSkyBox();

	void Initialize();
	void Destroy();
	void Update();
	void Render();

	void Reset();

	inline const D3DXVECTOR3* GetPositionAdress() { return &position; }


protected:

	float rotationAxisX = 0.0f;
	float rotationAxisY = 0.0f;

	static const int TRIANGLE_COUNT = 12;

	TextureTriangle triangles[TRIANGLE_COUNT];

	D3DXMATRIXA16 world;

	bool mouseLDown = false;
	POINT mouseStart;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 direction = D3DXVECTOR3(0, 0, 1);
	float moveSpeed = 10.0f;
	float rotationSpeed = 1.0f;


	float jumpPower = 10.0f;
	float jumpTime = 0.0f;
	bool isJumping = false;

	void Spin(float x, float y);

	LPDIRECT3DTEXTURE9 texture = nullptr;
};
