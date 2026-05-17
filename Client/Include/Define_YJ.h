#pragma once


#define DEAD 0
#define NOEVENT 1

#define PURE = 0
#define OBJ_DEAD 0
#define OBJ_NOEVENT 1

#define WINCX 800
#define WINCY 600

#define fDT GET_SINGLE(CTimeMgr_YJ)->GetDeltaTime();

typedef struct tagInfoYJ
{
	D3DXVECTOR3		vPos;	// 위치 벡터

	D3DXVECTOR3		vDir;	// 방향 벡터
	D3DXVECTOR3		vLook;

	D3DXVECTOR3		vNormal;	// 법선 벡터(방향 벡터)

	D3DXMATRIX		matWorld;


}VECYJINFO;


// 벡터의 상등 : 크기와 방향이 일치하는 두 벡터는 같은 벡터라고 말할 수 있다.
// 단위 벡터 : 벡터의 크기가 1인 벡터
// 벡터의 정규화 : 벡터의 크기를 1로 만드는 과정

// 벡터의 내적과 외적
// A(x,y,z)
// B(x`,y`,z`)

// 내적 : A ? B, 상수 = (x * x` + y * y` + z * z`), 상수곱(스칼라 곱)
// 외적 : A X B, 벡터 = (y * z` - z * y`, x * z` - z * x`, x * y` - y * x`), 벡터곱(방향 벡터)

// 행렬
// - 여러 개의 수를 행(가로)과 열(세로)의 형태로 모아놓은 형태
// - 객체의 여러 상태를 표현하기 위함(크기, 회전, 위치)

// 항등 행렬의 만들어주는 함수
// D3DXMATRIX	matScale, matRotZ, matTrans, matWorld;
// 
// // 행렬 관련 함수는 output 매개 변수가 들어올 경우 가장 먼저 항등 행렬로 초기화를 진행 한 뒤, 결과값을 반영
// 
// D3DXMatrixIdentity(&matWorld);		// 항등 행렬 생성
// 
// // 크기 행렬을 만들어주는 함수
// D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
// 
// // 회전 행렬을 만들어주는 함수
// D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(디그리 각도));
// 
// // 이동 행렬을 만들어주는 함수
// D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
// 
// matWorld = matScale * matRotZ * matTrans;

// 벡터와 행렬의 곱셈을 수행해주는 함수

// D3DXVec3TransformCoord(결과 값을 저장할 벡터(위치)의 주소, 행렬과 곱셈을 수행할 위치 벡터의 주소, 벡터와 곱셈을 수행할 행렬의 주소);
// D3DXVec3TransformNormal(결과 값을 저장할 벡터(방향)의 주소, 행렬과 곱셈을 수행할 방향 벡터의 주소, 벡터와 곱셈을 수행할 행렬의 주소);


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

static D3DXVECTOR3		GetMouse()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return D3DXVECTOR3((float)ptMouse.x, (float)ptMouse.y, 0.f);
}

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


#pragma region 벡터 전처리기 정의

namespace YJUTIL
{
	typedef		bool						_bool;

	typedef		signed char					_byte;
	typedef		unsigned char				_ubyte;

	typedef		wchar_t						_tchar;

	typedef		signed short				_short;
	typedef		unsigned short				_ushort;

	typedef		signed int					_int;
	typedef		unsigned int				_uint;

	typedef		signed long					_long;
	typedef		unsigned long				_ulong;

	typedef		float						_float;
	typedef		double						_double;

	typedef		D3DXVECTOR2					_vec2;
	typedef		D3DXVECTOR3					_vec3;
	typedef		D3DXVECTOR4					_vec4;

	typedef		D3DXMATRIX					_matrix;

	enum OBJ_TYPE { OBJ_PLAYER, OBJ_OBSTACLE, OBJ_BOSS, OBJ_MONSTER, OBJ_END };
}


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

#pragma endregion