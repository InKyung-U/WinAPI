#pragma once
#include "CStage.h"

class CObj;
class Stage_Y_04 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;
    CObj* m_pDoor02; 
    CObj* m_pDoor03;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_Y_04();
    ~Stage_Y_04();
};

