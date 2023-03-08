#pragma once
#include "CStage.h"
class CObj;
class Stage_R_02 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_R_02();
    ~Stage_R_02();

};

