#pragma once
#include "CStage.h"
class GameOver :
    public CStage
{
private:
    CTexture* m_pGameOverImg;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    GameOver();
    ~GameOver();
};

