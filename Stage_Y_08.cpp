#include "pch.h"
#include "Stage_Y_08.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"


Stage_Y_08::Stage_Y_08()
	: m_pGate01(nullptr)
{
	LoadTileFromFile(L"tile\\y_08");

}

Stage_Y_08::~Stage_Y_08()
{
}
void Stage_Y_08::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::R_02)
		pObj->SetPos(Vec2(64.f * 32 + 32, 64.f * 15));
	else
		pObj->SetPos(Vec2(64.f * 2, 64.f * 10));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 32 + 32, 64.f * 16));
	m_pGate01->SetScale(Vec2(64.f * 3, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

}

void Stage_Y_08::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::R_02);
	}
}

void Stage_Y_08::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_Y_08::Enter()
{
	init();
}

void Stage_Y_08::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
}

