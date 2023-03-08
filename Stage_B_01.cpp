#include "pch.h"
#include "Stage_B_01.h"

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


Stage_B_01::Stage_B_01()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
{
	LoadTileFromFile(L"tile\\b_01");
}

Stage_B_01::~Stage_B_01()
{
}

void Stage_B_01::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	m_pObj = new CPlayer;
	m_pObj->SetPos(Vec2(64.f * 10, 64.f * 1));
	m_pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(m_pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(m_pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0, 64.f * 9));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 20, 64.f * 9));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 4));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// ±×¸²
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 5 + 32, 64 * 4 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_01", L"texture\\b_bmp\\b_01.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 14 + 32, 64 * 4 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_02", L"texture\\b_bmp\\b_02.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

}

void Stage_B_01::update()
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

void Stage_B_01::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_B_01::Enter()
{
	CStageMgr::GetInst()->Setbgm(L"Inquiry");


	init();

	CCamera::GetInst()->FadeIn(0.8f);

}

void Stage_B_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
}
