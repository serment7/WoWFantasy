
#pragma once

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


#pragma warning (disable:4786)
#pragma warning (disable:4996)	

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <winuser.h>
#include <zmouse.h>
#include <math.h>
#include <set>
#include <map>
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Local Header Files
#include "d3dx9.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	DWORD		c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL, };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct ST_POS_SAMPLE
{
	float nKeyFrame;
	D3DXVECTOR3 v;
};

struct ST_ROT_SAMPLE
{
	float nKeyFrame;
	D3DXQUATERNION q;
};

struct ST_RAY
{
	D3DXVECTOR3 direction;
	D3DXVECTOR3 origin;
};

extern HWND g_hWnd;

#define TRACKTIME 12.0f

#define EPSILON 0.0001f
#define GET_WHEEL_DELTA_WPARAM(wParam)    ((short)HIWORD(wParam))

#define SAFE_RELEASE(p) {if (p) { (p)->Release(); (p) = NULL; }}
#define SAFE_ADD_REF(p) {if (p) { (p)->AddRef(); }}
#define SAFE_DELETE(p) {if (p) { delete (p); (p) = NULL; }}

//겟터 셋터 메크로
#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: inline varType Get##funName(void) const { return varName; }\
public: inline void Set##funName(varType var){ varName = var; }

#define SYNTHESIZE_PASS_BY_REF(varType, varName, funName)\
protected: varType varName;\
public: inline varType& Get##funName(void) { return varName; }\
public: inline void Set##funName(varType& var){ varName = var; }

#define SYNTHESIZE_ADD_REF(varType, varName, funName)\
protected: varType varName; \
public: virtual varType Get##funName(void) const { return varName; }\
public: virtual void Set##funName(varType var){\
	if (varName != var) { SAFE_ADD_REF(var); SAFE_RELEASE(varName); varName = var; }\
}

#define SINGLETONE(class_name) \
private:	\
	class_name();\
public:		\
	~class_name();\
	static class_name* GetInstance(void)\
	{\
		static class_name Instance;\
		return &Instance;\
	}

#include "cDeviceManager.h"
#include "timeManager.h"

#define STD_FILE_BUFFER 1024
#define BETWEENSIZE 1
