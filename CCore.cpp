#include "pch.h"
#include "CCore.h"

// Manager Header
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

CCore::CCore()
	: m_hWnd(nullptr)
	, m_hDC(nullptr)
	, m_ptResolution{}
	, m_hBackBitMap(nullptr)
	, m_hBackDC(nullptr)
	, m_hGreenPen(nullptr)
	, m_hRedPen(nullptr)
	, m_hFont(nullptr)
{
}

CCore::~CCore()
{
	(HFONT)SelectObject(m_hBackDC, m_holdFont);

	ReleaseDC(m_hWnd, m_hDC);

	DeleteObject(m_hBackBitMap);
	DeleteDC(m_hBackDC);

	DeleteObject(m_hGreenPen);
	DeleteObject(m_hRedPen);
	DeleteObject(m_hBluePen);
	DeleteObject(m_hFont);
}

int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;	

	// 윈도우 해상도에 맞는 크기로 재설정
	ChangeWindowSize(_ptResolution, false);

	// Pen 생성
	m_hGreenPen = CreatePen(PS_SOLID, 1, RGB(120, 255, 0));
	m_hRedPen = CreatePen(PS_SOLID, 1, RGB(255, 40, 40));
	m_hBluePen = CreatePen(PS_SOLID, 1, RGB(40, 40, 255));

	// DC 생성
	m_hDC = GetDC(m_hWnd);

	// ===============
	// BackBuffer 생성
	// ===============
	m_hBackBitMap = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hBackDC = CreateCompatibleDC(m_hDC);

	// Backbuffer DC 가 새로 만든 Bitmap 을 그리기 목적지로 선택한다
	HBITMAP hPrevBitMap = (HBITMAP)SelectObject(m_hBackDC, m_hBackBitMap);
	DeleteObject(hPrevBitMap);


	// =============
	// Manager 초기화
	// =============
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CStageMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSoundMgr::GetInst()->init();

	// Sound 로드 테스트
	//bgm
	CResMgr::GetInst()->LoadSound(L"title", L"sound\\title.wav");
	CResMgr::GetInst()->LoadSound(L"gameover", L"sound\\gameover.wav");
	CResMgr::GetInst()->LoadSound(L"Inquiry", L"sound\\Inquiry.wav");
	CResMgr::GetInst()->LoadSound(L"museum", L"sound\\museum.wav");
	CResMgr::GetInst()->LoadSound(L"opening", L"sound\\opening.wav");

	CResMgr::GetInst()->LoadSound(L"blood", L"sound\\blood.wav");
	CResMgr::GetInst()->LoadSound(L"cat", L"sound\\cat.wav");
	CResMgr::GetInst()->LoadSound(L"door_close", L"sound\\door_close.wav");
	CResMgr::GetInst()->LoadSound(L"door_not_open", L"sound\\door_not_open.wav");
	CResMgr::GetInst()->LoadSound(L"door_open", L"sound\\door_open.wav");
	CResMgr::GetInst()->LoadSound(L"glass_ton2", L"sound\\glass_ton2.wav");
	CResMgr::GetInst()->LoadSound(L"item_get", L"sound\\item_get.wav");
	CResMgr::GetInst()->LoadSound(L"key", L"sound\\key.wav");
	CResMgr::GetInst()->LoadSound(L"kutu_ib", L"sound\\kutu_ib_cut.wav");
	CResMgr::GetInst()->LoadSound(L"mizu_go", L"sound\\mizu_go.wav");
	CResMgr::GetInst()->LoadSound(L"monster1", L"sound\\monster1.wav");
	CResMgr::GetInst()->LoadSound(L"monster2", L"sound\\monster2.wav");
	CResMgr::GetInst()->LoadSound(L"monster3", L"sound\\monster3.wav");
	CResMgr::GetInst()->LoadSound(L"monster4", L"sound\\monster4.wav");

	CResMgr::GetInst()->LoadSound(L"select", L"sound\\select.wav");
	CResMgr::GetInst()->LoadSound(L"sneeze", L"sound\\sneeze.wav");
	CResMgr::GetInst()->LoadSound(L"table_move", L"sound\\table_move.wav");
	CResMgr::GetInst()->LoadSound(L"Monster_broken", L"sound\\Monster_broken.wav");
	CResMgr::GetInst()->LoadSound(L"PlayerHit", L"sound\\PlayerHit.wav");
	CResMgr::GetInst()->LoadSound(L"PressedAnt", L"sound\\PressedAnt.wav");
	CResMgr::GetInst()->LoadSound(L"RedBall", L"sound\\RedBall.wav");
	CResMgr::GetInst()->LoadSound(L"Word", L"sound\\Word.wav");

	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"title");
	pNewSound->PlayToBGM(true);

	//
	// 폰트 적용
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += L"font\\DOSMyungjo.ttf";
	AddFontResource(strFilePath.c_str());
	m_hFont = CreateFont(35, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
		VARIABLE_PITCH | FF_MODERN, L"DOSMyungjo");
	m_holdFont = (HFONT)SelectObject(m_hBackDC, m_hFont);
	SetTextColor(m_hBackDC, RGB(255, 255, 255));
	SetBkMode(m_hBackDC, TRANSPARENT);

	return S_OK;
}

void CCore::update()
{
	// ==============
	// Manager update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Stage Update
	// ============	
	CStageMgr::GetInst()->update();
	CUIMgr::GetInst()->update();

	// ===============
	// Collision Check
	// ===============
	CCollisionMgr::GetInst()->update();

	// ===========
	// Game Render
	// ===========
	// 화면 지우기
	Rectangle(m_hBackDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// Stage 그리기
	CStageMgr::GetInst()->render(m_hBackDC);
	CCamera::GetInst()->render(m_hBackDC);

	// BackBuffer 내용을 윈도우 비트맵으로 옮기기(복사)
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y, m_hBackDC, 0, 0, SRCCOPY);


	// ==========
	// Event 처리
	// ==========
	CEventMgr::GetInst()->update();
}

void CCore::ChangeWindowSize(POINT _ptResolution, bool _bMenu)
{
	RECT rt = { 0, 0, _ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hWnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_ptResolution = _ptResolution;
}
