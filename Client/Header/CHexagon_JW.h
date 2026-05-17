#pragma once
#include "CObj_JW.h"

#define SIZE_HEX_JW     40.f
#define SIZE_HEX_Z_JW   20.f
#define RATIO_HEX_X_JW  1.725f
#define RATIO_HEX_Y_JW  2.f
#define COUNT_HEX_VTX_JW   6

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

