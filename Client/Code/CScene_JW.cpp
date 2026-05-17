#include "pch.h"
#include "CScene_JW.h"

#include "CSpace_JW.h"
#include "CHexagon_JW.h"
#include "CObstacle_JW.h"

#include "CObjMgr_JW.h"
#include "CObstacleMgr_JW.h"

CScene_JW::CScene_JW()
{

}

CScene_JW::~CScene_JW()
{
	Release();
}

void CScene_JW::Initialize()
{
	CObj_JW* pHex = new CHexagon_JW;
	pHex->Initialize();

	CObjMgr_JW::GetInstance()->PushBackObj
	(
		ObjType_JW::Hexagon,
		pHex
	);
}

int CScene_JW::Update()
{
	CObstacleMgr_JW::GetInstance()->Update();
	CObjMgr_JW::GetInstance()->Update();

	return 0;
}

void CScene_JW::LateUpdate()
{
	CObjMgr_JW::GetInstance()->LateUpdate();

}

void CScene_JW::Render(HDC hDC)
{
	CObjMgr_JW::GetInstance()->Render(hDC);

}

void CScene_JW::Release()
{
	CObjMgr_JW::DestroyInstance();
	CObstacleMgr_JW::DestroyInstance();
}
