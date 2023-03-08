#pragma once
#include "CStage.h"

class CObj;
class Stage_B_04 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;
    CObj* m_pRose;
    CObj* m_pObj;

    float m_fAddTime;
    CObj* m_pText1;
    CObj* m_pText2;
    CObj* m_pText3;
    CObj* rose;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_B_04();
    ~Stage_B_04();
};

