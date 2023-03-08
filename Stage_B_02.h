#pragma once
#include "CStage.h"

class CObj;
class Stage_B_02 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;
    CObj* m_pObj;
    CObj* DoorText;
    float m_fAddTime;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_B_02();
    ~Stage_B_02();
};

