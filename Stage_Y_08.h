#pragma once
#include "CStage.h"

class CObj;
class Stage_Y_08 :
    public CStage
{
private:
    CObj* m_pGate01;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_Y_08();
    ~Stage_Y_08();
};

