#pragma once

class CCore
{
public:
	SINGLE(CCore);

private:
	HWND		m_hWnd;
	HDC			m_hDC;
	POINT		m_ptResolution;

	HBITMAP		m_hBackBitMap;
	HDC			m_hBackDC;

	HPEN		m_hGreenPen;
	HPEN		m_hRedPen;
	HPEN		m_hBluePen;

	HFONT		m_hFont;
	HFONT		m_holdFont;
	HDC			m_hdcAlpha;

	
public:
	int init(HWND _hWnd, POINT _ptResolution);
	void update();

public:
	HWND GetMainWndHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }	

	HDC GetAlphaDC() { return m_hdcAlpha; }

	HPEN GetGreenPen() { return m_hGreenPen; }
	HPEN GetRedPen() { return m_hRedPen; }
	HPEN GetBluePen() { return m_hBluePen; }

	void ChangeWindowSize(POINT _ptResolution, bool _bMenu);
};