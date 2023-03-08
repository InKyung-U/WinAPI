#include "pch.h"
#include "Stage_B_00.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CUI.h"
#include "CPanel.h"


Stage_B_00::Stage_B_00()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
{
	LoadTileFromFile(L"tile\\b_00");
}

Stage_B_00::~Stage_B_00()
{
}

void Stage_B_00::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::B_02)
		pObj->SetPos(Vec2(64.f * 1, 64.f * 8));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::B_04)
		pObj->SetPos(Vec2(64.f * 18, 64.f * 8));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0, 64.f * 9));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 20, 64.f * 9));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);


	// 그림
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 5 + 32, 64 * 4 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_01", L"texture\\b_bmp\\b_01.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 14 + 32, 64 * 4 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_02", L"texture\\b_bmp\\b_02.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);
}

// 00이 계단 없는 복도임

void Stage_B_00::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::B_02);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::B_04);
	}
}

void Stage_B_00::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_B_00::Enter()
{
	init();

	if (CStageMgr::GetInst()->IsPlayerHaveRose())
	{
		// UI 만들기
		Vec2 vScale = Vec2(120, 160);
		Vec2 vPos = Vec2(0.f, 0.f);
		CUI* pParentUI = nullptr;
		// UI 1
		pParentUI = new CPanel;
		pParentUI->SetPos(vPos);
		pParentUI->SetScale(vScale);
		AddObject(pParentUI, EOBJ_TYPE::UI);
	}

	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_B_00::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);

}
