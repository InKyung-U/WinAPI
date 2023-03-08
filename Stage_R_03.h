#pragma once
#include "CStage.h"
class Stage_R_03 :
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
    Stage_R_03();
    ~Stage_R_03();

};

