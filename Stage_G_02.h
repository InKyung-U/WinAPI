#pragma once
#include "CStage.h"

class CObj;
class Stage_G_02 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;
    CObj* m_pDoor02;
    CObj* m_pMonster;
    CObj* m_pGreenKey;
    CObj* m_pObj;
    CObj* m_pMonsterImg;

    float m_fAddTime;
    bool m_bMonsterCreate;
    CUI* pParentUI;


public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_G_02();
    ~Stage_G_02();
};

