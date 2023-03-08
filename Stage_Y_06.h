#pragma once
#include "CStage.h"

class CObj;
class Stage_Y_06 :
    public CStage
{
private:
    CObj* m_pDoor01;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_Y_06();
    ~Stage_Y_06();
};

