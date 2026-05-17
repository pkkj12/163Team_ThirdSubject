#pragma once
#include "Engine_Define.h"

#define EPSILON_JW			0.001f

#define OBJ_NOEVENT_JW		0
#define OBJ_DESTROY_JW		1
#define OBJ_HANDOVER_JW		2

inline bool Equals_JW(const float& fDst, const float& fSrc)
{
	return fabs(fDst - fSrc) < EPSILON_JW ? true : false;
}

#ifdef _DEBUG

typedef struct tagDebug_JW
{
	static void DBG_WindowText(const float& rF) 
	{
		wstring wsDBG = to_wstring(rF);
		SetWindowText(g_hWnd, wsDBG.c_str());
	}

	static void DBG_WindowText(const _vec3& rV)
	{
		wstring wsDBG = 
			to_wstring(rV.x) + L"/" +
			to_wstring(rV.y) + L"/" +
			to_wstring(rV.z);
		SetWindowText(g_hWnd, wsDBG.c_str());
	}

	static void DBG_WindowText(const wstring& rWs)
	{
		SetWindowText(g_hWnd, rWs.c_str());
	}
}DEBUG_JW;

#endif

typedef struct tagInfo_JW
{
	_vec3	vPos;
	_vec3	vDir;
	_vec3	vLook;

	_vec3	vScale;
	_vec3	vRotate;

	_matrix	matWorld;

	tagInfo_JW()
		: vPos({ 0.f, 0.f, 0.f }), vDir({ 0.f, 0.f, 0.f }), vLook({ 0.f, 0.f, 0.f }),
		vScale({ 1.f, 1.f, 1.f }), vRotate({ 0.f, 0.f, 0.f })
	{
		D3DXMatrixIdentity(&matWorld);
	}
}INFO_JW;

enum class ObjType_JW
	: _ushort
{
	Obstacle,	// 장애물, 사다리꼴
	Player,		// 삼각형

	Hexagon,	// 육각형

	End
};