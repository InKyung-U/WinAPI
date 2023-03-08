#include "pch.h"
#include "Stage_M_1F_pic.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CTexture.h"
#include "CText.h"
#include "CPicture.h"

Stage_M_1F_pic::Stage_M_1F_pic()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
	, m_text1(nullptr)
	, m_text2(nullptr)
{
	LoadTileFromFile(L"tile\\m_1F_big_pic");
}

Stage_M_1F_pic::~Stage_M_1F_pic()
{
}
void Stage_M_1F_pic::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_2F_01)
		pObj->SetPos(Vec2(64.f * 2, 64.f * 10));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_2F_02)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 10));

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 1, 64.f * 10));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 20, 64.f * 10));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 그림

	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 10, 64 * 4));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"big_pic01", L"texture\\ib\\big_pic01.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	m_text1 = new CText;
	m_text1->SetPos(Vec2(64 * 10, 64 * 6 + 32));
	m_text1->SetScale(Vec2(20, 20));
	m_text1->SetUIScript(L"\'???의 세계\'\n어려워서 읽을 수 없는 글자가 있다...");
	m_text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(m_text1, EOBJ_TYPE::TEXT);

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		m_text2 = new CText;
		m_text2->SetPos(Vec2(64 * 8, 64 * 6 + 32));
		m_text2->SetScale(Vec2(20, 20));
		m_text2->SetUIScript(L"액자 뒤에서 파란 액체가 흘러내린다...");
		m_text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"물감1", L"texture\\M_objectbmp\\물감1.bmp"));
		AddObject(m_text2, EOBJ_TYPE::TEXT);
	}

}

void Stage_M_1F_pic::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_2F_01);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_2F_02);
	}

	if (((CText*)m_text1)->IsScriptSearchDone())
	{
		if(CStageMgr::GetInst()->IsSubCharOff() == false)
			CStageMgr::GetInst()->SetbgmDecrescendo(3.f);

		CStageMgr::GetInst()->SubCharTurnOff();
	}

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		if (((CText*)m_text2)->IsScriptSearchDone())
		{
			m_text2->SetUIScript(L"\"아래로 내려오렴 이브\n비밀의 장소 알려줄게\"");
			m_text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"물감2", L"texture\\M_objectbmp\\물감2.bmp"));
			CStageMgr::GetInst()->MuseumSearchDone();
		}
	}
}

void Stage_M_1F_pic::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_M_1F_pic::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_1F_pic::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::SCRIPTUI);
	Clear(EOBJ_TYPE::TEXT);

}


