#include "pch.h"
#include "Stage_Y_04.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"

Stage_Y_04::Stage_Y_04()
	: m_pGate01(nullptr)
	, m_pDoor01(nullptr)
	, m_pDoor02(nullptr)
	, m_pDoor03(nullptr)
{
	LoadTileFromFile(L"tile\\y_04");

}

Stage_Y_04::~Stage_Y_04()
{
}

void Stage_Y_04::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::G_01)
		pObj->SetPos(Vec2(64.f * 12 + 32, 64.f * 27));
	else if (CStageMgr::GetInst()->GetPrevDoor() == 1)
		pObj->SetPos(Vec2(64.f * 5 + 32, 64.f * 12));
	else if (CStageMgr::GetInst()->GetPrevDoor() == 2)
		pObj->SetPos(Vec2(64.f * 33 + 32, 64.f * 12));
	else if (CStageMgr::GetInst()->GetPrevDoor() == 3)
		pObj->SetPos(Vec2(64.f * 33 + 32, 64.f * 23));
	else
		pObj->SetPos(Vec2(64.f * 12 + 32, 64.f * 25));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 12 + 32, 64.f * 29));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// door
	// 1 거짓말
	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 5 + 32, 64.f * 10));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);

	// 2 사과
	m_pDoor02 = new CDoor;
	m_pDoor02->SetPos(Vec2(64.f * 33 + 32, 64.f * 10));
	m_pDoor02->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor02, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);

	// 3 입
	m_pDoor03 = new CDoor;
	m_pDoor03->SetPos(Vec2(64.f * 33 + 32, 64.f * 21));
	m_pDoor03->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor03, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);
}

void Stage_Y_04::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::G_01);
	}
	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CStageMgr::GetInst()->SetPrevDoor(1);
			ChangeStage(ESTAGE_TYPE::Y_05);
		}
	}
	if (((CDoor*)m_pDoor02)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CStageMgr::GetInst()->SetPrevDoor(2);
			ChangeStage(ESTAGE_TYPE::Y_07);
		}
	}
	if (((CDoor*)m_pDoor03)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
		{
			CStageMgr::GetInst()->SetPrevDoor(3);
			ChangeStage(ESTAGE_TYPE::Y_08);
		}
	}
}

void Stage_Y_04::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_Y_04::Enter()
{
	init();
}

void Stage_Y_04::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
}
