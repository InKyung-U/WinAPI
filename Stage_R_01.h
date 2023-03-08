#pragma once
#include "CStage.h"

class Stage_R_01 :
    public CStage
{
private:

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_R_01();
    ~Stage_R_01();

};

