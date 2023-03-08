#pragma once
#include "CStage.h"


class CStage_Start :
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
    CStage_Start();
    ~CStage_Start();
};

