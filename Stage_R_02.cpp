#include "pch.h"
#include "Stage_R_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"

Stage_R_02::Stage_R_02()
	: m_pGate01(nullptr)
	, m_pDoor01(nullptr)
{
	LoadTileFromFile(L"tile\\r_02");

}

Stage_R_02::~Stage_R_02()
{
}

void Stage_R_02::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::Y_08)
		pObj->SetPos(Vec2(64.f * 2 + 32, 64.f * 2));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 2 + 32, 64.f * 0));
	m_pGate01->SetScale(Vec2(64.f * 3, 64.f));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 23 + 32, 64.f * 6));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);

}

void Stage_R_02::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::Y_08);
	}
	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
			ChangeStage(ESTAGE_TYPE::R_01);
	}

}

void Stage_R_02::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_R_02::Enter()
{
	init();
}

void Stage_R_02::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
}
