#include "pch.h"
#include "CStage_Play01.h"


#include "CStageMgr.h"
#include "CKeyMgr.h"
#include "CCollisionMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CMonster.h"
#include "CForcePoint.h"
#include "CBlock.h"


CStage_Play01::CStage_Play01()
{
}

CStage_Play01::~CStage_Play01()
{
}

void CStage_Play01::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	CObj* pObj = new CPlayer;
	pObj->SetPos(Vec2( (float)ptResolution.x / 2.f, 100.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	// Monster 추가
	CObj* pMonster = new CMonster;
	pMonster->SetPos(Vec2((float)ptResolution.x, 0.f));
	pMonster->SetScale(Vec2(100.f, 100.f));
	pMonster->GetCollider()->SetScale(pMonster->GetScale());

	AddObject(pMonster, EOBJ_TYPE::MONSTER);


	// Block 배치
	CObj* pBlock = new CBlock;
	pBlock->SetPos(Vec2(1280 / 2.f, 600.f));
	pBlock->SetScale(Vec2(500.f, 100.f));
	AddObject(pBlock, EOBJ_TYPE::BLOCK);


	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER_PROJECTILE, EOBJ_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::MONSTER_PROJECTILE, EOBJ_TYPE::PLAYER);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::BLOCK);
}

void CStage_Play01::update()
{
	CStage::update();

	if (KTAP(KEY::ENTER))
	{
		ChangeStage(ESTAGE_TYPE::TOOL);
	}	

	if (KTAP(KEY::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		CreateForce(EOBJ_TYPE::PLAYER, vMousePos, 1000.f, 300.f, 0.2f);
	}
}

void CStage_Play01::render(HDC _dc)
{
	CStage::render(_dc);

	TextOut(_dc, 10, 10, L"Here Is Play01 Stage", (int)wcslen(L"Here Is Play01 Stage"));
}

void CStage_Play01::Enter()
{
	init();	
	
	// LoadTileFromFile(L"tile\\temp2.tile");

	//CCamera::GetInst()->FadeOut(2.f);
	//CCamera::GetInst()->FadeIn(0.5f);
}

void CStage_Play01::Exit()
{
	Clear();
}