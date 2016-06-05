#pragma once

#define g_pDeviceManager cDeviceManager::GetInstance()
#define g_pD3DDevice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager  
{
	SINGLETONE(cDeviceManager);
private:	
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	LPDIRECT3DTEXTURE9	m_pD3DTexture;

public:

	LPDIRECT3DDEVICE9 GetDevice();
	LPDIRECT3DTEXTURE9 GetTexture();
	void Destroy();

};