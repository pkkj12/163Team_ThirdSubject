#pragma once

#include "pch.h"

#define PURE_SM	= 0

#define OBJ_NOEVENT_SM  0
#define OBJ_DEAD_SM		1

#define VK_MAX			0xff

typedef struct tagInfo_SM
{
	D3DXVECTOR3	vPos;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vNormal;

	D3DXMATRIX matWorld;

}INFO_SM;