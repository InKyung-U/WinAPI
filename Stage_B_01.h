#pragma once
#include "CStage.h"

class CObj;
class Stage_B_01 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pGate02;

    CObj* m_pObj;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_B_01();
    ~Stage_B_01();
};

