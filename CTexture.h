#pragma once
#include "CRes.h"


class CTexture :
    public CRes
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;

    BITMAP      m_info;

public:
    HDC GetDC() { return m_hDC; }
    UINT Width() { return m_info.bmWidth; }
    UINT Height() { return m_info.bmHeight; }


private:
    int Load(const wstring& _strFullPath) override;
    int Create(UINT _iWidth, UINT _iHeight);

public:
    CTexture();
    ~CTexture();

    friend class CResMgr;
};

