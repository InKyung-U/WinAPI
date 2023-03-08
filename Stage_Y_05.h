#pragma once
#include "CStage.h"
class Stage_Y_05 :
    public CStage
{
private:
    CObj* m_pDoor01;
    CObj* m_pDoor02;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_Y_05();
    ~Stage_Y_05();
};

