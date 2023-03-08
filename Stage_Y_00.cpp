#include "pch.h"
#include "Stage_Y_00.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"

Stage_Y_00::Stage_Y_00()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
{
	LoadTileFromFile(L"tile\\y_00");

}

Stage_Y_00::~Stage_Y_00()
{
}
void Stage_Y_00::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::Y_02)
		pObj->SetPos(Vec2(64.f * 5, 64.f * 8 + 32));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::Y_03)
		pObj->SetPos(Vec2(64.f * 14, 64.f * 8 + 32));
	else 
		pObj->SetPos(Vec2(64.f * 9 + 32, 64.f * 10));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 4, 64.f * 8 + 32));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 15, 64.f * 8 + 32));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

}

void Stage_Y_00::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::Y_02);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::Y_03);
	}

	if (KTAP(KEY::ENTER))
	{
		ChangeStage(ESTAGE_TYPE::Y_01);
	}
}

void Stage_Y_00::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_Y_00::Enter()
{
	init();
}

void Stage_Y_00::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
}

