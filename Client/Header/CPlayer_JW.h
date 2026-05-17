#pragma once
#include "CObj_JW.h"

#define SIZE_TRIANGLE_JW        20.f
#define DISTANCE_TRIANGLE_JW    100.f // 중점간의 거리

class CPlayer_JW :
    public CObj_JW
{
public:
    explicit CPlayer_JW();
    virtual ~CPlayer_JW();
public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
private:
    void Key_Input();

#ifdef _DEBUG
private:
    void DBG_WindowText();
#endif
};

