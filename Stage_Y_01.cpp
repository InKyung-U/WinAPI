#include "pch.h"
#include "Stage_Y_01.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"

// °í¾çÀÌ¸Ê¿¡¼­ ±æ ¶Õ¸°°Å

Stage_Y_01::Stage_Y_01()
	: m_pGate01(nullptr)
{
	LoadTileFromFile(L"tile\\y_01");
}

Stage_Y_01::~Stage_Y_01()
{
}

void Stage_Y_01::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 9 + 32, 64.f * 6 + 32));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 9 + 32, 64.f * 1));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

}

void Stage_Y_01::update()
{
	CStage::update();
}

void Stage_Y_01::render(HDC _dc)
{
	CStage::render(_dc);
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::Y_04);
	}
}

void Stage_Y_01::Enter()
{
	init();
}

void Stage_Y_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
}

