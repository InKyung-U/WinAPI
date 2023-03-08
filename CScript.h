#pragma once
#include "CUI.h"

class CTexture;
class CScript :
    public CUI
{
private:
    CTexture* m_pUITex;
    bool m_bShowScript;
    Vec2 m_vScriptBoxPos;
    Vec2 m_vScriptBoxScale;

    wstring m_sScript;

public:
    void SetScriptBoxPos(Vec2 _pos) { m_vScriptBoxPos = _pos; }

public:
    virtual void update() override;
    virtual void render(HDC _dc) override;

    virtual void EraseScript() { m_bShowScript = false; }
    virtual void ShowScript() { m_bShowScript = true; }

    void SetUIScript(const wstring& _str) { m_sScript = _str; }

public:
    virtual void MouseLbtnClicked(Vec2 _vMousePos) override;

    CLONE(CScript);

public:
    CScript();
    ~CScript();
};

