#pragma once
#include "CStage.h"

class CStage_Play01 :
    public CStage
{
private:

public:
    void init() override;
    void update() override;
    void render(HDC) override;


    void Enter() override;
    void Exit() override;


public:
    CStage_Play01();
    ~CStage_Play01();
};

