#pragma once
#include "CStage.h"
class Stage_G_03 :
    public CStage
{
private:
    CObj* m_pDoor01;
    CObj* m_pDoor02;
    CObj* m_pMonster;
    CObj* pObj;
    CObj* text1;
    float m_fAddTime;
    CUI* pParentUI;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_G_03();
    ~Stage_G_03();
};

