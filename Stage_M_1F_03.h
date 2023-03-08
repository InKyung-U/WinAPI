#pragma once
#include "CStage.h"

class CObj;
class Stage_M_1F_03 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pGate02;

    CObj* m_pic2;
    float m_fAddTime;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_M_1F_03();
    ~Stage_M_1F_03();
};

