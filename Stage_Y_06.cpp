#include "pch.h"
#include "Stage_Y_06.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"

Stage_Y_06::Stage_Y_06()
	: m_pDoor01(nullptr)
{
	LoadTileFromFile(L"tile\\y_06");

}

Stage_Y_06::~Stage_Y_06()
{
}

void Stage_Y_06::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 10 + 32, 64.f * 11));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 10 + 32, 64.f * 11));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);
}

void Stage_Y_06::update()
{
	CStage::update();
	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
			ChangeStage(ESTAGE_TYPE::Y_05);
	}

}

void Stage_Y_06::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_Y_06::Enter()
{
	init();
}

void Stage_Y_06::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
}
