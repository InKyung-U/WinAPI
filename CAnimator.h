#pragma once
#include "CComponent.h"

class CAnimation;
class CTexture;

class CAnimator :
    public CComponent
{
private:
    map<wstring, CAnimation*>   m_mapAnim;
    CAnimation*                 m_pCurAnim;
    bool                        m_bRepeat;

public:
    void update() override;
    void render(HDC _dc) override;

    void Play(const wstring& _strName, bool _bRepeat = true);

public:
    void CreateAnimation(const wstring& _strAnimName, CTexture* _pAtlasTex, Vec2 _vLeftTop, Vec2 _vSize, float _fXDistance, float _fDuration, UINT _iFrmCount);

    CAnimation* FindAnimation(const wstring& _strName);    

    void LoadAnimation(const wstring& _strRelativeFilePath);

    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _origin);
    ~CAnimator();
};

