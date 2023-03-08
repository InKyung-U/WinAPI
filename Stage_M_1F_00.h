#pragma once
#include "CStage.h"

class CObj;
class CTexture;
class CSound;
class Stage_M_1F_00 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pGate02;
    CObj* pObj;
    CObj* window2;
    CObj* mainGate;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_M_1F_00();
    ~Stage_M_1F_00();
};

