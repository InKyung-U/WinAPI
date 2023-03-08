#include "pch.h"
#include "Stage_Y_07.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CKeyMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CDoor.h"

Stage_Y_07::Stage_Y_07()
	:m_pDoor01(nullptr)

{
	LoadTileFromFile(L"tile\\y_07");

}

Stage_Y_07::~Stage_Y_07()
{
}

void Stage_Y_07::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 9 + 32, 64.f * 10));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pDoor01 = new CDoor;
	m_pDoor01->SetPos(Vec2(64.f * 9 + 32, 64.f * 11));
	m_pDoor01->SetScale(Vec2(64.f, 64.f * 2));
	AddObject(m_pDoor01, EOBJ_TYPE::DOOR);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::DOOR);
}

void Stage_Y_07::update()
{
	CStage::update();

	if (((CDoor*)m_pDoor01)->IsDoorEnter())
	{
		if (KTAP(KEY::SPACE))
			ChangeStage(ESTAGE_TYPE::Y_04);
	}

}

void Stage_Y_07::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_Y_07::Enter()
{
	init();
}

void Stage_Y_07::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);

}
