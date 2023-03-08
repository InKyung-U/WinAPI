#include "pch.h"
#include "CItemMenu.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CCamera.h"

CItemMenu::CItemMenu()
	: m_pCharTex(nullptr)
	, m_pMenuTex(nullptr)
	, m_pItem1(nullptr)
	, m_pItem2(nullptr)
	, m_pItem3(nullptr)
{
	m_pMenuTex = CResMgr::GetInst()->LoadTexture(L"Menu", L"texture\\ib\\itemMenu.bmp");
	m_pCharTex = CResMgr::GetInst()->LoadTexture(L"Menu_ib", L"texture\\ib\\menu_ib.bmp");

	m_pItem1 = CResMgr::GetInst()->LoadTexture(L"item_01", L"texture\\item\\item_01.bmp");

}

CItemMenu::~CItemMenu()
{
}

void CItemMenu::init()
{
}

void CItemMenu::update()
{
	CStage::update();

	if (KTAP(KEY::ESC))
	{
		ChangeStage(CStageMgr::GetInst()->GetPrevStageType());
	}


}

void CItemMenu::render(HDC _dc)
{
	BitBlt(_dc
		, 0, 0
		, m_pMenuTex->Width()
		, m_pMenuTex->Height()
		, m_pMenuTex->GetDC()
		, 0, 0
		, SRCCOPY);

	BitBlt(_dc
		, 180, 130
		, m_pCharTex->Width()
		, m_pCharTex->Height()
		, m_pCharTex->GetDC()
		, 0, 0
		, SRCCOPY);

	BitBlt(_dc
		, 550, 200
		, m_pItem1->Width()
		, m_pItem1->Height()
		, m_pItem1->GetDC()
		, 0, 0
		, SRCCOPY);

	if (m_pItem2 != nullptr)
	{
		BitBlt(_dc
			, 550, 200 + m_pItem1->Height() + 20
			, m_pItem2->Width()
			, m_pItem2->Height()
			, m_pItem2->GetDC()
			, 0, 0
			, SRCCOPY);
	}

	if (m_pItem3 != nullptr)
	{
		BitBlt(_dc
			, 550, 200 + m_pItem1->Height() + 40 + m_pItem2->Height()
			, m_pItem3->Width()
			, m_pItem3->Height()
			, m_pItem3->GetDC()
			, 0, 0
			, SRCCOPY);
	}
}

void CItemMenu::Enter()
{
	if (CStageMgr::GetInst()->IsPlayerHaveRose())
	{
		m_pItem2 = CResMgr::GetInst()->LoadTexture(L"item_02", L"texture\\item\\item_02.bmp");
	}


	if (CStageMgr::GetInst()->IsHaveBlueKey())
	{
		m_pItem3 = CResMgr::GetInst()->LoadTexture(L"item_03", L"texture\\item\\item_03.bmp");
	}
	else if (CStageMgr::GetInst()->HaveAntPic())
	{
		m_pItem3 = CResMgr::GetInst()->LoadTexture(L"item_04", L"texture\\item\\item_04.bmp");
	}
	else if (CStageMgr::GetInst()->IsHaveGreenKey())
	{
		m_pItem3 = CResMgr::GetInst()->LoadTexture(L"item_05", L"texture\\item\\item_05.bmp");
	}
	else
		m_pItem3 = nullptr;
}

void CItemMenu::Exit()
{
}
