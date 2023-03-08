#pragma once
#include "CStage.h"

class CObj;
class Stage_B_03 :
    public CStage
{
private:
    CObj* m_pObj;
    CObj* BlueKey;
    CObj* pic2;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_B_03();
    ~Stage_B_03();
};

