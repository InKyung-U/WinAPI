#include "pch.h"
#include "Stage_M_1F_01_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CText.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_M_1F_01_02::Stage_M_1F_01_02()
	:m_pGate01(nullptr)
	, m_pGate02(nullptr)
	, m_pGate03(nullptr)
	, m_pGate04(nullptr)
{
	LoadTileFromFile(L"tile\\m_1F_01_2");

}

Stage_M_1F_01_02::~Stage_M_1F_01_02()
{
}

void Stage_M_1F_01_02::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_00)
		pObj->SetPos(Vec2(64.f + 32, 896.f));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_02)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 14));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_03)
		pObj->SetPos(Vec2(64.f * 10, 64.f * 23));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0 + 32, 64.f * 14));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 20, 64.f * 14));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);

	m_pGate03 = new CGate;
	m_pGate03->SetPos(Vec2(64.f * 10, 64.f * 25));
	m_pGate03->SetScale(Vec2(64.f * 6, 64.f * 1));
	AddObject(m_pGate03, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	m_pGate04 = new CGate;
	m_pGate04->SetPos(Vec2(64 * 10, 64 * 12 + 32));
	m_pGate04->SetScale(Vec2(64.f * 4, 64.f * 1));
	AddObject(m_pGate04, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);


	// 오브젝트
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 10, 64 * 4));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"pic1", L"texture\\M_objectbmp\\그림1.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 10, 64 * 6 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 5 + 32, 64 * 4 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text1", L"texture\\M_objectbmp\\텍스트1.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 10, 64 * 14 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"fish", L"texture\\M_objectbmp\\fish.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 10, 64 * 18 + 32));
	text3->SetScale(Vec2(70, 30));
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명1", L"texture\\M_objectbmp\\설명1.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 8 + 32, 64 * 11 + 32));
	pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"step", L"texture\\M_objectbmp\\step.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_1F_01_02::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_00);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_02);
	}
	else if (((CGate*)m_pGate03)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_03);
	}
	else if (((CGate*)m_pGate04)->IsGateTouched())
	{
		CSound* dive = CResMgr::GetInst()->FindSound(L"mizu_go");
		dive->Play();

		ChangeStage(ESTAGE_TYPE::B_01);
	}
}

void Stage_M_1F_01_02::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_M_1F_01_02::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_1F_01_02::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
}
