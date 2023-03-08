#include "pch.h"
#include "Stage_R_01.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"

Stage_R_01::Stage_R_01()
{
	LoadTileFromFile(L"tile\\r_01");

}

Stage_R_01::~Stage_R_01()
{
}
void Stage_R_01::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2(64.f * 4, 64.f * 20));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

}

void Stage_R_01::update()
{
	CStage::update();
	
}

void Stage_R_01::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_R_01::Enter()
{
	init();
}

void Stage_R_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);

}

