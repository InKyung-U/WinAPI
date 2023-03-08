#include "pch.h"
#include "Stage_R_03.h"
#include "CCore.h"
#include "CPlayer.h"

Stage_R_03::Stage_R_03()
{
	LoadTileFromFile(L"tile\\r_03");

}

Stage_R_03::~Stage_R_03()
{
}

void Stage_R_03::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 9 + 32, 64.f * 10));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();
}

void Stage_R_03::update()
{
	CStage::update();

}

void Stage_R_03::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_R_03::Enter()
{
	init();
}

void Stage_R_03::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);

}
