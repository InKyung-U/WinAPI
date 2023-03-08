#include "pch.h"
#include "Stage_M_1F_02.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CText.h"

Stage_M_1F_02::Stage_M_1F_02()
	: m_pGate01(nullptr)
	, m_pGate02(nullptr)
{
	LoadTileFromFile(L"tile\\m_1F_02");

}

Stage_M_1F_02::~Stage_M_1F_02()
{
}

void Stage_M_1F_02::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01)
		pObj->SetPos(Vec2(64.f, 64.f * 11));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_01_02)
		pObj->SetPos(Vec2(64.f, 64.f * 11));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_03)
		pObj->SetPos(Vec2(64.f * 2, 64.f * 33));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0 , 64.f * 11));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 0 + 32, 64.f * 33));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 그림
	
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 3 + 32, 64 * 6 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_01", L"texture\\미술관그림bmp\\1_01.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 7 + 32, 64 * 6 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_02", L"texture\\미술관그림bmp\\1_02.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	CObj* pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 11 + 32, 64 * 6 + 32));
	pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_03", L"texture\\미술관그림bmp\\1_03.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CObj* pic4 = new CPicture;
	pic4->SetPos(Vec2(64 * 15 + 32, 64 * 6 + 32));
	pic4->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_04", L"texture\\미술관그림bmp\\1_04.bmp"));
	AddObject(pic4, EOBJ_TYPE::PIC);

	CObj* pic5 = new CPicture;
	pic5->SetPos(Vec2(64 * 6 + 32, 64 * 28 + 32));
	pic5->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_05", L"texture\\미술관그림bmp\\1_05.bmp"));
	AddObject(pic5, EOBJ_TYPE::PIC);

	CObj* pic6 = new CPicture;
	pic6->SetPos(Vec2(64 * 2 + 32, 64 * 28 + 32));
	pic6->SetTexture(CResMgr::GetInst()->LoadTexture(L"1_06", L"texture\\미술관그림bmp\\1_06.bmp"));
	AddObject(pic6, EOBJ_TYPE::PIC);

	// 오브젝트
	CObj* obj1 = new CPicture;
	obj1->SetPos(Vec2(64 * 11, 64 * 22));
	obj1->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_06", L"texture\\M_objectbmp\\m_06.bmp"));
	AddObject(obj1, EOBJ_TYPE::PIC);

	CObj* obj2 = new CPicture;
	obj2->SetPos(Vec2(64 * 17, 64 * 21));
	obj2->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_06", L"texture\\M_objectbmp\\m_06.bmp"));
	AddObject(obj2, EOBJ_TYPE::PIC);

	// 텍스트
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 3+ 32, 64 * 7 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetUIScript(L"\'물가의 ??\'\n어려워서 읽을 수 없는 글자가 있다...");
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 7 + 32, 64 * 7 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetUIScript(L"\'지평선의 풍경\'");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 11 + 32, 64 * 7 + 32));
	text3->SetScale(Vec2(20, 20));
	text3->SetUIScript(L"\'??의 잔\'\n어려워서 읽을 수 없는 글자가 있다...");
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* text4 = new CText;
	text4->SetPos(Vec2(64 * 15 + 32, 64 * 7 + 32));
	text4->SetScale(Vec2(20, 20));
	text4->SetUIScript(L"\'??의 정신\'\n어려워서 읽을 수 없는 글자가 있다...");
	text4->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text4, EOBJ_TYPE::TEXT);

	CObj* text5 = new CText;
	text5->SetPos(Vec2(64 * 6 + 32, 64 * 29 + 32));
	text5->SetScale(Vec2(20, 20));
	text5->SetUIScript(L"\'어느 언덕에서 본 하늘\'");
	text5->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text5, EOBJ_TYPE::TEXT);

	CObj* text6 = new CText;
	text6->SetPos(Vec2(64 * 2 + 32, 64 * 29 + 32));
	text6->SetScale(Vec2(20, 20));
	text6->SetUIScript(L"\'개성없는 파수꾼\'");
	text6->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text6, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 6 + 32, 64 * 30));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m02_01", L"texture\\bmp_char\\1m02_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

		CObj* subC2 = new CText;
		subC2->SetPos(Vec2(64 * 12 + 32, 64 * 19));
		subC2->SetScale(Vec2(30, 60));
		subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m02_03", L"texture\\bmp_char\\1m02_03.bmp"));
		AddObject(subC2, EOBJ_TYPE::TEXT);

		CObj* subC3 = new CText;
		subC3->SetPos(Vec2(64 * 12 + 32, 64 * 20));
		subC3->SetScale(Vec2(30, 60));
		subC3->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m02_02", L"texture\\bmp_char\\1m02_02.bmp"));
		AddObject(subC3, EOBJ_TYPE::TEXT);

		CObj* subC4 = new CText;
		subC4->SetPos(Vec2(64 * 15 + 32, 64 * 15));
		subC4->SetScale(Vec2(30, 60));
		subC4->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m02_04", L"texture\\bmp_char\\1m02_04.bmp"));
		AddObject(subC4, EOBJ_TYPE::TEXT);
	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_1F_02::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		if (CStageMgr::GetInst()->IsMuseumSearchDone())
			ChangeStage(ESTAGE_TYPE::M_1F_01_02);
		else
			ChangeStage(ESTAGE_TYPE::M_1F_01);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_03);
	}
}

void Stage_M_1F_02::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_M_1F_02::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_1F_02::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);

}

