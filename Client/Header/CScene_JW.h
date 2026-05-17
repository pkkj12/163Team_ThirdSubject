#pragma once
#include "CBase.h"
#include "CScene.h"

class CScene_JW :
    public CScene
{
public:
    CScene_JW();
    virtual ~CScene_JW();

public:
    void Initialize() override;
    int  Update() override;
    void LateUpdate() override;
    void Render(HDC hDC) override;
    void Release() override;
};

