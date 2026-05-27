#include "pch.h"
#include "CLine.h"
#include "CLineMgr.h"
#include "CScrollMgr.h"
#include "CKeyMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{
	m_vecPoint.reserve(100);
	//ZeroMemory(m_vecPoint, sizeof(D3DXVECTOR3) * DIR_END);
}

CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/PLATFORM.bmp", L"PLATFORM");
}

void CLineMgr::Update()
{
	POINT	pt{};
	GetCursorPos(&pt);
	ScreenToClient(g_hEditorWnd, &pt);


	pt.x -= (int)CScrollMgr::GetInstance()->Get_ScrollX();
	pt.y -= (int)CScrollMgr::GetInstance()->Get_ScrollY();

	D3DXVECTOR3 vMouse{ (float)pt.x, (float)pt.y, 0.f };
	// 점 찍기
	if (CKeyMgr::GetInstance()->Key_Down(VK_LBUTTON))
	{
		if (!m_vecPoint.empty())
		{
			D3DXVECTOR3 vPrev = m_vecPoint.back();

			// 이전 점 -> 현재 점 라인 생성
			m_Linelist.push_back(new CLine(vPrev, vMouse));
		}

		m_vecPoint.push_back(vMouse);
	}

	// C키: 마지막 점 -> 첫 점 연결해서 폐곡선 완성
	if (CKeyMgr::GetInstance()->Key_Down('S'))
	{
		if (m_vecPoint.size() >= 3)
		{
			DATA tData{};
			lstrcpy(tData.szName, L"OBSTACLE");

			tData.vCenter = GetPolygonCentroid(m_vecPoint);

			for (size_t i = 0; i < m_vecPoint.size(); ++i)
			{
				LINE_DATA tLine{};

				tLine.tBegin = m_vecPoint[i];

				tLine.tEnd =
					m_vecPoint[(i + 1) % m_vecPoint.size()];

				tLine.fThickness = 10.f;

				// 저장용 데이터
				tData.vecLineData.push_back(tLine);

				// 실제 렌더/충돌용 선 생성
				m_Linelist.push_back(
					new CLine(
						tLine.tBegin,
						tLine.tEnd
					)
				);
			}

			// 오브젝트 등록
			m_ObjList.push_back(tData);

		}

		m_vecPoint.clear();
	}

	// ESC: 현재 찍던 점 취소
	if (CKeyMgr::GetInstance()->Key_Down(VK_ESCAPE))
	{
		m_vecPoint.clear();
	}

	//if (CKeyMgr::GetInstance()->Key_Down(VK_LBUTTON))
	//{
	//	m_vPoint[LEFT].x= (float)pt.x;
	//	m_vPoint[LEFT].y = (float)pt.y;
	//}

	//if (CKeyMgr::GetInstance()->Key_Up(VK_LBUTTON))
	//{
	//	m_vPoint[RIGHT].x = (float)pt.x;
	//	m_vPoint[RIGHT].y = (float)pt.y;

	//	m_Linelist.push_back(new CLine(m_vPoint[LEFT], m_vPoint[RIGHT]));
	//}


	//몬스터
	//if (CKeyMgr::Get_Instance()->Key_Down('W'))
	//{
	//	DATA tData{};
	//	tData.fX = (float)pt.x;
	//	tData.fY = (float)pt.y;
	//	lstrcpy(tData.szName, L"MONSTER"); 
	//
	//	m_ObjList.push_back(tData);
	//}

	//발판
	//if (CKeyMgr::GetInstance()->Key_Down('Q'))
	//{
	//	DATA tData{};
	//	tData.fX = (float)pt.x;
	//	tData.fY = (float)pt.y;
	//	tData.fCX = 163.f;
	//	tData.fCY = 50.f;
	//	lstrcpy(tData.szName, L"PLATFORM");

	//	m_ObjList.push_back(tData);
	//}

	//CKeyMgr::GetInstance()->Key_Up('Q');
}

void CLineMgr::LateUpdate()
{
	Key_Input();
}

void CLineMgr::Render(HDC hDC)
{
	for (auto& pLine : m_Linelist)
		pLine->Render(hDC);

	int iScrollX = (int)CScrollMgr::GetInstance()->Get_ScrollX();
	int iScrollY = (int)CScrollMgr::GetInstance()->Get_ScrollY();



	// 선 미리보기
	if (!m_vecPoint.empty())
	{
		POINT pt{};
		GetCursorPos(&pt);
		ScreenToClient(g_hEditorWnd, &pt);

		pt.x -= (int)CScrollMgr::GetInstance()->Get_ScrollX();
		pt.y -= (int)CScrollMgr::GetInstance()->Get_ScrollY();

		D3DXVECTOR3 vLast = m_vecPoint.back();

		MoveToEx(hDC,
			(int)(vLast.x + CScrollMgr::GetInstance()->Get_ScrollX()),
			(int)(vLast.y + CScrollMgr::GetInstance()->Get_ScrollY()),
			nullptr);

		LineTo(hDC,
			(int)(pt.x + CScrollMgr::GetInstance()->Get_ScrollX()),
			(int)(pt.y + CScrollMgr::GetInstance()->Get_ScrollY()));
	}

	//for (auto& obj : m_ObjList)
	//{
	//	//HDC hMemDC = CBmpMgr::Get_Instance()->Find_Image(obj.szName);
	//	//조건문으로 오브젝트마다 각각 크기 수정가능
	//	//if (!lstrcmp(obj.szName, L"PLATFORM") && hMemDC)
	//	//{						//여기에 크기 절반만큼 빼주면 중심점에 생성	  //여기에 이미지 크기값
	//	//	BitBlt(hDC, (int)obj.fX - 81 + iScrollX, (int)obj.fY - 50 + iScrollY, 163, 100, hMemDC, 0, 0, SRCCOPY);
	//	//	//나중에 색깔 빼는 함수로 수정
	//	//}
	//}
}

void CLineMgr::Release()
{
	for_each(m_Linelist.begin(), m_Linelist.end(), Safe_Delete<CLine*>);
	m_Linelist.clear();
}


void CLineMgr::Save_Data()
{
	HANDLE hFile = CreateFile(L"../Data/ObjectLine.dat", // 파일 이름을 포함한 경로
		GENERIC_WRITE,            // 파일 모드
		NULL,                    // 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정할 수 있다
		NULL,                    // 보안 속성, NULL 인 경우 기본 값 상태
		CREATE_ALWAYS,            // 쓰기 전용 옵션(파일이 없으면 생성하여 저장) / OPEN_EXSITING(파일이 있을 경우만 불러오기) 
		FILE_ATTRIBUTE_NORMAL,    // 파일 속성(아무런 속성 없는 일반 파일)
		NULL);                    // 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않아서 NULL)

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hEditorWnd, L"Save File", _T("Fail"), MB_OK);
		return;
	}
	else
	{
		DWORD    dwByte(0);


		int iObjCount = (int)m_ObjList.size();
		WriteFile(hFile, &iObjCount, sizeof(int), &dwByte, nullptr);


		for (auto& obj : m_ObjList)
		{
			WriteFile(hFile, obj.szName, sizeof(TCHAR) * 32, &dwByte, nullptr);


			WriteFile(hFile, &obj.vCenter, sizeof(D3DXVECTOR3), &dwByte, nullptr);


			int iLineCount = (int)obj.vecLineData.size();

			WriteFile(hFile, &iLineCount, sizeof(int), &dwByte, nullptr);
			// 라인 데이터 저장
			for (auto& line : obj.vecLineData)
			{
				WriteFile(hFile, &line, sizeof(LINE_DATA), &dwByte, nullptr);
			}

		}
		CloseHandle(hFile);
	}

	//HANDLE hObjFile = CreateFile(L"../Data/Object.dat", // 파일 이름을 포함한 경로
	//	GENERIC_WRITE,            // 파일 모드
	//	NULL,                    // 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해서 설정할 수 있다
	//	NULL,                    // 보안 속성, NULL 인 경우 기본 값 상태
	//	CREATE_ALWAYS,            // 쓰기 전용 옵션(파일이 없으면 생성하여 저장) / OPEN_EXSITING(파일이 있을 경우만 불러오기) 
	//	FILE_ATTRIBUTE_NORMAL,    // 파일 속성(아무런 속성 없는 일반 파일)
	//	NULL);                    // 생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않아서 NULL)

	//if (hObjFile == INVALID_HANDLE_VALUE)
	//{
	//	MessageBox(g_hEditorWnd, L"Save File", _T("Fail"), MB_OK);
	//	return;
	//}
	//else
	//{
	//	DWORD    dwByte(0);
	//	for (auto& hObj : m_ObjList)
	//	{
	//		WriteFile(hObjFile, &hObj, sizeof(DATA), &dwByte, NULL);
	//	}
	//	CloseHandle(hObjFile);
	//}

	MessageBox(g_hEditorWnd, L"Save 완료", _T("Success"), MB_OK);
}
void CLineMgr::Load_Data()
{
	HANDLE hFile = CreateFile(
		L"../Data/ObjectLine.dat",
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	if (hFile == INVALID_HANDLE_VALUE)
		return;

	DWORD dwByte = 0;

	// 기존 데이터 제거
	for (auto& pLine : m_Linelist)
		delete pLine;

	m_Linelist.clear();
	m_ObjList.clear();

	int iObjCount = 0;
	ReadFile(hFile, &iObjCount, sizeof(int), &dwByte, nullptr);

	for (int i = 0; i < iObjCount; ++i)
	{
		DATA obj{};

		ReadFile(hFile, obj.szName, sizeof(TCHAR) * 32, &dwByte, nullptr);

		ReadFile(hFile, obj.vCenter, sizeof(D3DXVECTOR3), &dwByte, nullptr);

		int iLineCount = 0;
		ReadFile(hFile, &iLineCount, sizeof(int), &dwByte, nullptr);

		for (int j = 0; j < iLineCount; ++j)
		{
			LINE_DATA line{};
			ReadFile(hFile, &line, sizeof(LINE_DATA), &dwByte, nullptr);

			obj.vecLineData.push_back(line);

			// 실제 렌더/충돌용 라인도 다시 생성
			m_Linelist.push_back(
				new CLine(
					line.tBegin,
					line.tEnd
				)
			);
		}

		m_ObjList.push_back(obj);
	}
}
void CLineMgr::Key_Input()
{
	if (GetAsyncKeyState(VK_RIGHT))
		CScrollMgr::GetInstance()->Set_ScrollX(-5.f);

	if (GetAsyncKeyState(VK_LEFT))
		CScrollMgr::GetInstance()->Set_ScrollX(5.f);

	if (GetAsyncKeyState(VK_UP))
		CScrollMgr::GetInstance()->Set_ScrollY(5.f);

	if (GetAsyncKeyState(VK_DOWN))
		CScrollMgr::GetInstance()->Set_ScrollY(-5.f);


	if (GetAsyncKeyState('C'))
	{
		Save_Data();
		return;
	}
	if (GetAsyncKeyState('L'))
	{
		Load_Data();
		return;
	}
}

D3DXVECTOR3 CLineMgr::GetObjectCenter(const vector<D3DXVECTOR3>& points)
{
	D3DXVECTOR3 vCenter{0.f,0.f,0.f};

	if (points.empty()) return vCenter;

	for (auto& p : points)
		vCenter += p;

	vCenter /= (float)points.size();

	return vCenter;
}

D3DXVECTOR3 CLineMgr::GetPolygonCentroid(const vector<D3DXVECTOR3>& points)
{
	float area = 0.f;
	float cx = 0.f;
	float cy = 0.f;

	int count = (int)points.size();

	for (int i = 0; i < count; ++i)
	{
		const auto& p0 = points[i];
		const auto& p1 = points[(i + 1) % count];

		float cross = p0.x * p1.y - p1.x * p0.y;

		area += cross;
		cx += (p0.x + p1.x) * cross;
		cy += (p0.y + p1.y) * cross;
	}

	area *= 0.5f;

	if (fabsf(area) < 0.0001f)
		return GetObjectCenter(points);

	D3DXVECTOR3 center{};
	center.x = cx / (6.f * area);
	center.y = cy / (6.f * area);
	center.z = 0.f;

	return center;
}
