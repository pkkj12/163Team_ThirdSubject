#pragma once

class CTimeMgr_YJ
{
	DECLARE_SINGLE(CTimeMgr_YJ);
public:
	void Initialize();
	void Update();
	void ResetTime();

	unsigned __int32 GetFps() { return _fps; }
	float GetDeltaTime() { return _deltaTime; }
	DWORD GetCurSec() { return m_curSec; }

private:
	unsigned __int64 _frequency = 0;
	unsigned __int64 _prevCount = 0;
	float _deltaTime = 0.f;

private:
	unsigned __int32 _frameCount = 0;
	float _frameTime = 0.f;
	unsigned __int32 _fps = 0;

private:
	DWORD m_dwTime;
	DWORD m_curSec;
};

