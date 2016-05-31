// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstring>

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
#include<d3d9.h>
#include<d3dx9.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

extern HWND g_hWnd;

#define SAFE_RELEASE(p) {if(p) {(p)->Release(); p=nullptr;}}
#define SAFE_DELETE(p) {if(p) {delete (p); p=nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p) {delete[] (p); p=nullptr;}}

#define OUT
#define IN

#define EPSILON 0.0001f

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	float		u;
	float		v;
	ST_PNT_VERTEX()
		: p(0.0f, 0.0f, 0.0f)
		, n(0.0f, 0.0f, 0.0f)
		, u(0.0f)
		, v(0.0f)
	{}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n)
		: p(_p)
		, n(_n)
		, u(0.0f)
		, v(0.0f)
	{}
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct BoundingSphere
{
	D3DXVECTOR3 vCenter;
	float		fRadius;

	BoundingSphere( const D3DXVECTOR3& _vCenter, const float& fRadius)
		: vCenter(_vCenter)
		, fRadius(fRadius)
	{

	}
	bool IsPointIn(const D3DXVECTOR3& _point)
	{
		D3DXVECTOR3 length = _point - vCenter;
		if (D3DXVec3LengthSq(&(length))< fRadius*fRadius )
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct BoundingBox
{
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;

	BoundingBox()
		: vMin(0,0,0)
		, vMax(0,0,0)
	{};
	BoundingBox(const D3DXVECTOR3& _min, const D3DXVECTOR3& _max) { vMin = _min; vMax = _max; };

	bool IsPointIn(const D3DXVECTOR3& _point)
	{
		if (_point.x >= vMin.x && _point.x <= vMax.x
			&& _point.y >= vMin.y && _point.y <= vMax.y
			&& _point.z >= vMin.z && _point.z <= vMax.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

#include <cassert>
#include <list>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <queue>

#include "cDeviceManager.h"
#include "cTimeManager.h"
#include "cGameManager.h"
#include "cObjectManager.h"
#include "cAllocateHierarchy.h"
#include "cTextureManager.h"
#include "cSpriteManager.h"

#define STD_FILE_BUFFER 1024
#define BETWEENSIZE 1