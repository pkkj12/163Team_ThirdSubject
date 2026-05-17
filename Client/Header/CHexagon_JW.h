#pragma once
#include "CObj_JW.h"

#define SIZE_HEX_JW     40.f
#define RATIO_HEX_X_JW  1.725f
#define RATIO_HEX_Y_JW  2.f

class CHexagon_JW :
    public CObj_JW
{
public:
    explicit CHexagon_JW();
    virtual ~CHexagon_JW();
public:
    void Initialize() override;
    int  Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;

private:
    virtual void Free() override;
};

