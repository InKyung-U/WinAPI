#include "pch.h"
#include "Stage_Y_03.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"

Stage_Y_03::Stage_Y_03()
	: m_pGate01(nullptr)
{
	LoadTileFromFile(L"tile\\y_03");

}

Stage_Y_03::~Stage_Y_03()
{
}

void Stage_Y_03::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 4, 64.f * 8 +32));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 3, 64.f * 8 + 32));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

}

void Stage_Y_03::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::Y_00);
	}
}

void Stage_Y_03::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_Y_03::Enter()
{
	init();
}

void Stage_Y_03::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
}
