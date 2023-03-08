#pragma once
#include "CStage.h"

class CObj;
class Stage_B_00 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pGate02;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_B_00();
    ~Stage_B_00();
};

