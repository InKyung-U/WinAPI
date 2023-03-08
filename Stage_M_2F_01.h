#pragma once
#include "CStage.h"

class CGate;
class CTexture;
class Stage_M_2F_01 :
    public CStage
{
private:
    CGate* m_pGate01;
    CGate* m_pGate02;
    CGate* m_pGate03;
    CTexture* m_pTex;
    CObj* subC2;
    CObj* window1;
    CObj* pObj;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_M_2F_01();
    ~Stage_M_2F_01();
};

