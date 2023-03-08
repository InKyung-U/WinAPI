#pragma once
#include "CStage.h"

class CObj;
class Stage_G_01 :
    public CStage
{
private:
    CObj* m_pGate01;
    CObj* m_pDoor01;
    CObj* pObj;
    CObj* text1;

    CObj* m_pHand1;
    CObj* m_pHand2;
    CObj* m_pHand3;
    CObj* m_pHand4;

    CObj* m_pAnt;
    float m_fAddTime;
    CUI* pParentUI;


	wstring m_sTakePic;
	wstring m_sNotTakePic;
	CTexture* m_pSelectBox;
	Vec2    m_vSelectBoxPos;
	UINT m_iScriptNum;
    float m_fAlpha;

public:
    void init() override;
    void update() override;
    void render(HDC _dc) override;

    void Enter() override;
    void Exit() override;


public:
    Stage_G_01();
    ~Stage_G_01();
};

