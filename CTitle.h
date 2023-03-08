#pragma once
#include "CStage.h"

class CTexture;

class CTitle :
    public CStage
{
private:
    CTexture* m_pTiltleImg;
    CTexture* m_pScriptBox;
    CTexture* m_pSelectBox;
    Vec2    m_vSelectBoxPos;

    wstring m_pScript1;
    wstring m_pScript2;

    UINT m_iScriptNum;
    float m_fAddTime;
    float m_fAlpha;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    CTitle();
    ~CTitle();
};

