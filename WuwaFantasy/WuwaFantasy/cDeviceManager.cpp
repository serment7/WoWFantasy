#include "stdafx.h"
#include "cDeviceManager.h"

cDeviceManager::cDeviceManager()
	: m_pD3D(nullptr)
	, m_pD3DDevice(nullptr)
{
	int nVertexProcessing = 0;
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	D3DCAPS9 caps;
	
	m_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (caps.DevCaps&D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}
	D3DPRESENT_PARAMETERS stD3Dpp;
	ZeroMemory(&stD3Dpp, sizeof(D3DPRESENT_PARAMETERS));
	stD3Dpp.AutoDepthStencilFormat = D3DFMT_D24X8;
	stD3Dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	stD3Dpp.EnableAutoDepthStencil = TRUE;
	stD3Dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3Dpp.Windowed = TRUE;

	HRESULT hr = m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, nVertexProcessing, &stD3Dpp, &m_pD3DDevice);

	if (hr != D3D_OK)
	{
		int i;
		switch (hr)
		{
		case D3DERR_INVALIDCALL:
			i = 1;
			break;
		case D3DERR_OUTOFVIDEOMEMORY:
			i = 2;
			break;
		case D3DERR_NOTAVAILABLE:
			i = 3;
			break;
		}
	}
	assert(hr == D3D_OK && "디바이스 생성에 실패하였습니다");
}


cDeviceManager::~cDeviceManager()
{
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	if (m_pD3DDevice)
	{
		ULONG ul = m_pD3DDevice->Release();
		assert(ul == 0 && "디바이스로 만들푳E낸 객체 중 소툈E프갋않은 객체가 있습니다");
		m_pD3DDevice = nullptr;
	}

	SAFE_RELEASE(m_pD3D);
}
