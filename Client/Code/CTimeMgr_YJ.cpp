#include "pch.h"
#include "CTimeMgr_YJ.h"

CTimeMgr_YJ* CTimeMgr_YJ::m_pInstance = nullptr;

CTimeMgr_YJ::CTimeMgr_YJ()
{

}
CTimeMgr_YJ::~CTimeMgr_YJ()
{

}

void CTimeMgr_YJ::Initialize()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&_frequency));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_prevCount)); // CPU Å¬·°
}

void CTimeMgr_YJ::Update()
{
	unsigned __int64 currentCount;
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currentCount));

	_deltaTime = (currentCount - _prevCount) / static_cast<float>(_frequency);
	_prevCount = currentCount;

	_frameCount++;
	_frameTime += _deltaTime;

	if (_frameTime >= 1.f)
	{
		_fps = static_cast<unsigned __int32>(_frameCount / _frameTime);

		_frameTime = 0.f;
		_frameCount = 0;
	}


	if (m_dwTime + 1000 < GetTickCount()) {
		m_curSec++;
		m_dwTime = GetTickCount();
	}

}

void CTimeMgr_YJ::ResetTime()
{
	m_curSec = 0;
	m_dwTime = GetTickCount();
}