#pragma once
#define WINCX 800
#define WINCY 600

#define PURE = 0

#define OBJ_NOEVENT		0
#define OBJ_DEAD		1

extern HWND g_hWnd;

//typedef struct tagInfo
//{
//	float	fX, fY;
//	float	fCX, fCY;
//
//}INFO;

enum DIRECTION { LEFT, RIGHT, DIR_END };

//enum TYPE { line, MONSTER, END };

enum OBJID { PLAYER, BULLET, MONSTER, SHIELD, MOUSE, OBJ_END };


template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct tagDelete
{
	template<typename T>
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

struct tagDeleteMap
{
	template<typename T>
	void operator()(T& Pair)
	{
		if (Pair.second)
		{
			delete Pair.second;
			Pair.second = nullptr;
		}
	}
};

//typedef struct tagLinePoint
//{
//	D3DXVECTOR3 vPoint;
//
//	tagLinePoint()
//	{
//		ZeroMemory(this, sizeof(tagLinePoint));
//	}
//	tagLinePoint(D3DXVECTOR3 _vPoint)
//		: vPoint(_vPoint)
//	{
//
//	}
//
//}LINEPOINT;

typedef struct tagLine
{
	D3DXVECTOR3 tLeft;
	D3DXVECTOR3 tRight;
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(D3DXVECTOR3& _tLeft, D3DXVECTOR3& _tRight)
		: tLeft(_tLeft), tRight(_tRight)
	{

	}

}LINE;

#pragma region 싱글톤 전처리기 정의

#define DECLARE_SINGLE(classname)						\
private:												\
	classname();										\
	~classname();									\
	classname(const classname& rhs) = delete;			\
	classname& operator=(classname& rhs) = delete;	\
public:													\
	static classname* GetInstance()						\
	{													\
		if (!m_pInstance)								\
		{												\
			m_pInstance = new classname;				\
		}												\
		return m_pInstance;								\
	}													\
	static void Destroy_Instance()						\
	{													\
		if (m_pInstance)								\
		{												\
			delete m_pInstance;							\
			m_pInstance = nullptr;						\
		}												\
	}													\
														\
private:												\
static classname* m_pInstance;							\

#define GET_SINGLE(classname)	classname::GetInstance()

#pragma endregion
// 라인 데이터 구조체
typedef struct tagLineData
{
	D3DXVECTOR3 tBegin;
	D3DXVECTOR3 tEnd;
	float fThickness;
	int iGroupID;
	tagLineData()
	{
		ZeroMemory(this, sizeof(LINE_DATA));
	}

	tagLineData(const D3DXVECTOR3& _tBegin, const D3DXVECTOR3& _tEnd, float _fThickness, int _iGroupID)
		: tBegin(_tBegin), tEnd(_tEnd), fThickness(_fThickness), iGroupID(_iGroupID)
	{
	}
}LINE_DATA;



typedef struct OBJ_SAVE_DATA
{
	TCHAR szName[32];
	D3DXVECTOR3 vCenter;
	vector<LINE_DATA> vecLineData;
}DATA;