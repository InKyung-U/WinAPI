#pragma once
#include "CStage.h"
class EndStage :
    public CStage
{
private:
    CTexture* m_pEndTiltleImg;
    CTexture* m_pImgIB;

    float m_fAddTime;
    bool m_bChangeScene;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    EndStage();
    ~EndStage();
};

