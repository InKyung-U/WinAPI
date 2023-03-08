#pragma once
#include "CObj.h"

#include "CStage.h"

typedef  void(CStage::* stagememfunc)(void);

struct tStageDelegate
{
    CStage*         pStage;
    stagememfunc    pMemFunc;

public:
    void AddDynamic(CStage* _Stage, stagememfunc _pFunc)
    {
        pStage = _Stage;
        pMemFunc = _pFunc;
    }
};


class CUI :
    public CObj
{
private:
    vector<CUI*>    m_vecChildUI;
    Vec2            m_vFinalPos;
    CUI*            m_pParent;

    Vec2            m_vLbtnPressedPos;
    bool            m_bMouseOn;
    bool            m_bMouseLbtnPressed;


    // Stage Delegate
    tStageDelegate  m_ClickDelegate;

public:
    void AddChildUI(CUI* _pUI) {
        m_vecChildUI.push_back(_pUI);
        _pUI->m_pParent = this;
    }

    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

    Vec2 GetFinalPos() { return m_vFinalPos; }
    Vec2 GetLbtnPressedPos() {return m_vLbtnPressedPos;}
    void SetLbtnPressedPos(Vec2 _vPos) { m_vLbtnPressedPos = _vPos; }
    bool IsMouseOn() { return m_bMouseOn; }
    bool IsLbtnPressed() {return m_bMouseLbtnPressed;}

    void DragDrop_update();

    tStageDelegate& GetClickDelegate() {return m_ClickDelegate;}

public:
    virtual void update() override;    
    virtual void render(HDC _dc);
    virtual bool IsMouseOn(Vec2 _vMouseRealPos);


    // UI 위에서 마우스가 눌린 시점에 호출되는 함수
    virtual void MouseLbtnDown(Vec2 _vMousePos)
    {
        m_bMouseLbtnPressed = true;
        m_vLbtnPressedPos = _vMousePos;
    }

    virtual void MouseLbtnUp(Vec2 _vMousePos)
    {

    }

    // UI 에 MouseLbtnDown() 이 발생하고, 다시 UI 위에서 버튼이 떼진경우
    virtual void MouseLbtnClicked(Vec2 _vMousePos);
    
    CLONE(CUI);

public:
    CUI();
    CUI(const CUI& _origin);
    ~CUI();

    friend class CUIMgr;
};

