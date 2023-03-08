#pragma once
#include "CObj.h"

class CTexture;
class CUI;
class CText :
    public CObj
{
private:
    CTexture* m_pTex;
    bool m_bTouchText;
    bool m_bScriptExist;
    CUI* pParentUI;
    bool m_bScriptSearchDone;
    wstring m_sScript;
    UINT m_iScriptCount;
    UINT m_iScriptMaxCount;

   wstring m_lscriptList[3];


public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void SetScale(Vec2 _scale);
    bool IsPlayerContectText() { return m_bTouchText; }
    bool IsScriptSearchDone() { return m_bScriptSearchDone; }
    virtual void SetUIScript(const wstring& _str) { m_sScript = _str; }
    bool IsScriptOn() { return m_bScriptExist; }
    bool SetScriptCount(UINT _count) { m_iScriptMaxCount = _count; }
    void SetScriptList(wstring _list[3]) 
    {
        m_lscriptList[0] = _list[0];
        m_lscriptList[1] = _list[1];
        m_lscriptList[2] = _list[2];

        if (m_lscriptList[2].size() != 0)
            m_iScriptMaxCount = 3;
        else if (m_lscriptList[1].size() != 0)
            m_iScriptMaxCount = 2;
    }
    UINT GetScriptCount() { return m_iScriptCount; }

public:
    virtual void OnCollisionEnter(CObj* _pOtherObj) override;
    virtual void OnCollisionExit(CObj* _pOtherObj) override;

    virtual void SetTexture(CTexture* _tex) { m_pTex = _tex; }


    CLONE(CText);
public:
    CText();
    ~CText();
};

