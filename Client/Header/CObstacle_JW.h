#pragma once
#include "CObj_JW.h"
#include "CHexagon_JW.h"

#define RATIO_THICK_OBS_JW 0.3f

class CObstacle_JW :
    public CObj_JW
{
public:
    explicit CObstacle_JW();
    virtual ~CObstacle_JW();

public:
    void Initialize() override;
    int Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;

private:
    int     m_iSideIDX;
    float   m_fDistance;
    float   m_fSpeed;
};

