#pragma once
#include "CStage.h"

class CStartAnimation :
    public CStage
{
private:
    CObj* m_pPlayer;
    CObj* m_pMather;
    CObj* m_pFather;
    CObj* m_pScript;

    float m_fAddTime;
    bool m_stageScript1_On;
    bool m_stageScript2_On;
    bool m_stageScript3_On;
    UINT m_iScriptCount;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    CStartAnimation();
    ~CStartAnimation();
};

