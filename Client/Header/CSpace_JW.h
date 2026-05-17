#pragma once
#include "Define_JW.h"
#include "CObj_JW.h"

#define SPACE_ROT_JW 0.03f

class CSpace_JW :
    public CObj_JW
{
public:
    explicit CSpace_JW();
    virtual ~CSpace_JW();

public:

    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;

private:
    _ulong m_dwTurnTime;

    _ulong m_dwCurTime          = GetTickCount();
    const _ulong m_dwFirstTime  = GetTickCount();
};

