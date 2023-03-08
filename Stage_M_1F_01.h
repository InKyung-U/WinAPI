#pragma once
#include "CStage.h"

class CObj;
class Stage_M_1F_01 :
    public CStage
{

private:
    CObj* m_pGate01;
    CObj* m_pGate02;
    CObj* m_pGate03;



public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_M_1F_01();
    ~Stage_M_1F_01();
};

