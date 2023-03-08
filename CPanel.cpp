#include "pch.h"
#include "CPanel.h"
#include "CTexture.h"

#include "CResMgr.h"
#include "CStageMgr.h"

CPanel::CPanel()
	: m_pUITex()
{
	CResMgr::GetInst()->LoadTexture(L"r1", L"texture\\UIrose\\r1.bmp");
	CResMgr::GetInst()->LoadTexture(L"r2", L"texture\\UIrose\\r2.bmp");
	CResMgr::GetInst()->LoadTexture(L"r3", L"texture\\UIrose\\r3.bmp");
	CResMgr::GetInst()->LoadTexture(L"r4", L"texture\\UIrose\\r4.bmp");
	m_pUITex = CResMgr::GetInst()->LoadTexture(L"r5", L"texture\\UIrose\\r5.bmp");

}

CPanel::~CPanel()
{
}

void CPanel::update()
{
	//DragDrop_update();

	UINT roseCount = CStageMgr::GetInst()->GetRoseCount();

	if (roseCount == 1)
		m_pUITex = CResMgr::GetInst()->FindTexture(L"r1");
	else if (roseCount == 2)
		m_pUITex = CResMgr::GetInst()->FindTexture(L"r2");
	else if (roseCount == 3)
		m_pUITex = CResMgr::GetInst()->FindTexture(L"r3");
	else if (roseCount == 4)
		m_pUITex = CResMgr::GetInst()->FindTexture(L"r4");
	else if (roseCount == 5)
		m_pUITex = CResMgr::GetInst()->FindTexture(L"r5");



	CUI::update();
}

void CPanel::render(HDC _dc)
{
	//CUI::render(_dc);

	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	BitBlt(_dc
	, GetPos().x, GetPos().y
	, GetScale().x, GetScale().y
	, m_pUITex->GetDC()
	, 0, 0
	, SRCCOPY);
}

void CPanel::MouseLbtnClicked(Vec2 _vMousePos)
{
	CUI::MouseLbtnClicked(_vMousePos);
}