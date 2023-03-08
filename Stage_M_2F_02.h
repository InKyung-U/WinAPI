#pragma once
#include "CStage.h"

class CGate;
class Stage_M_2F_02 :
    public CStage
{
private:
    CGate* m_pGate01;
    CGate* m_pGate02;
    CObj* pic3;
    CObj* pObj;
    float m_fAddTime;

    bool m_bCat;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_M_2F_02();
    ~Stage_M_2F_02();
};

