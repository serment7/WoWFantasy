#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
{
}


cSkyBox::~cSkyBox()
{
	Destroy();
}

void cSkyBox::Initialize()
{
	rotationAxisX = 0.0f;
	rotationAxisY = 0.0f;

	const int VERTEX_COUNT = 8;
	D3DXVECTOR3 vertex[VERTEX_COUNT];
	vertex[0] = D3DXVECTOR3(-512.0f, -512, -512);
	vertex[1] = D3DXVECTOR3(-512, -512, 512);
	vertex[2] = D3DXVECTOR3(512, -512, 512);
	vertex[3] = D3DXVECTOR3(512, -512, -512);
	vertex[4] = D3DXVECTOR3(-512, 512, -512);
	vertex[5] = D3DXVECTOR3(-512, 512, 512);
	vertex[6] = D3DXVECTOR3(512, 512, 512);
	vertex[7] = D3DXVECTOR3(512, 512, -512);

	float uBase = 0.25;
	float vBase = 0.3333f;

	//아래
	triangles[0] = TextureTriangle(vertex[0], vertex[1], vertex[2],
		D3DXVECTOR2(uBase * 1, vBase * 3), D3DXVECTOR2(uBase * 1, vBase * 2), D3DXVECTOR2(uBase * 2, vBase * 2));
	triangles[1] = TextureTriangle(vertex[0], vertex[2], vertex[3],
		D3DXVECTOR2(uBase * 1, vBase * 2), D3DXVECTOR2(uBase * 2, vBase * 3), D3DXVECTOR2(uBase * 2, vBase * 2));

	//왼
	triangles[2] = TextureTriangle(vertex[4], vertex[5], vertex[1],
		D3DXVECTOR2(uBase * 1, vBase * 1), D3DXVECTOR2(uBase * 0, vBase * 1), D3DXVECTOR2(uBase * 0, vBase * 2));
	triangles[3] = TextureTriangle(vertex[4], vertex[1], vertex[0],
		D3DXVECTOR2(uBase * 1, vBase * 1), D3DXVECTOR2(uBase * 0, vBase * 2), D3DXVECTOR2(uBase * 1, vBase * 2));

	//위
	triangles[4] = TextureTriangle(vertex[7], vertex[6], vertex[5],
		D3DXVECTOR2(uBase * 2, vBase * 1), D3DXVECTOR2(uBase * 2, vBase * 0), D3DXVECTOR2(uBase * 1, vBase * 0));
	triangles[5] = TextureTriangle(vertex[7], vertex[5], vertex[4],
		D3DXVECTOR2(uBase * 2, vBase * 1), D3DXVECTOR2(uBase * 1, vBase * 0), D3DXVECTOR2(uBase * 1, vBase * 1));

	//오
	triangles[6] = TextureTriangle(vertex[3], vertex[2], vertex[6],
		D3DXVECTOR2(uBase * 2, vBase * 2), D3DXVECTOR2(uBase * 3, vBase * 2), D3DXVECTOR2(uBase * 3, vBase * 1));
	triangles[7] = TextureTriangle(vertex[3], vertex[6], vertex[7],
		D3DXVECTOR2(uBase * 2, vBase * 2), D3DXVECTOR2(uBase * 3, vBase * 1), D3DXVECTOR2(uBase * 2, vBase * 1));

	//뒤
	triangles[8] = TextureTriangle(vertex[1], vertex[5], vertex[6],
		D3DXVECTOR2(uBase * 4, vBase * 2), D3DXVECTOR2(uBase * 4, vBase * 1), D3DXVECTOR2(uBase * 3, vBase * 1));
	triangles[9] = TextureTriangle(vertex[1], vertex[6], vertex[2],
		D3DXVECTOR2(uBase * 4, vBase * 2), D3DXVECTOR2(uBase * 3, vBase * 1), D3DXVECTOR2(uBase * 3, vBase * 2));

	//앞
	triangles[10] = TextureTriangle(vertex[4], vertex[0], vertex[3],
		D3DXVECTOR2(uBase * 1, vBase * 1), D3DXVECTOR2(uBase * 1, vBase * 2), D3DXVECTOR2(uBase * 2, vBase * 2));
	triangles[11] = TextureTriangle(vertex[4], vertex[3], vertex[7],
		D3DXVECTOR2(uBase * 1, vBase * 1), D3DXVECTOR2(uBase * 2, vBase * 2), D3DXVECTOR2(uBase * 2, vBase * 1));

	D3DXCreateTextureFromFile(
		g_pD3DDevice,
		"./Resource/Box/sky.png",
		&texture);
}

void cSkyBox::Destroy()
{
	SAFE_RELEASE(texture);
}

void cSkyBox::Update()
{
	D3DXMATRIXA16 sc;
	D3DXMatrixScaling(&sc, 200, 200, 200);
	world = sc;
	D3DXMATRIX rotX, rotY, move;
	D3DXMatrixRotationX(&rotX, rotationAxisX);
	D3DXMatrixRotationY(&rotY, rotationAxisY);

	world = rotX * rotY;

	D3DXVECTOR3 baseDirection(0, 0, 1);
	D3DXVec3TransformCoord(&direction,
		&baseDirection, &world);


	D3DXMatrixTranslation(&move, position.x, position.y, position.z);

}

void cSkyBox::Render()
{
	g_pD3DDevice->SetRenderState(
		D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);
	g_pD3DDevice->SetTexture(0, texture);
	g_pD3DDevice->SetFVF(FVF_PositionTexture::FVF);
	g_pD3DDevice->DrawPrimitiveUP(
		D3DPT_TRIANGLELIST,
		TRIANGLE_COUNT,
		&triangles[0],
		sizeof(FVF_PositionTexture));
	g_pD3DDevice->SetRenderState(
		D3DRS_LIGHTING, true);
}


void cSkyBox::Spin(float x, float y)
{
	rotationAxisY -= x;
	rotationAxisX -= y;
}

void cSkyBox::Reset()
{
	rotationAxisX = 0.0f;
	rotationAxisY = 0.0f;

	position = D3DXVECTOR3(0, 0, 0);
	direction = D3DXVECTOR3(0, 0, 1);

	mouseLDown = false;
}