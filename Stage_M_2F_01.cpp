#include "pch.h"
#include "Stage_M_2F_01.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CTexture.h"
#include "CText.h"
#include "CPicture.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_M_2F_01::Stage_M_2F_01()
	: m_pTex()
{
	LoadTileFromFile(L"tile\\m_2F_01");
}

Stage_M_2F_01::~Stage_M_2F_01()
{
}

void Stage_M_2F_01::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	// Player 추가
	pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_00)
		pObj->SetPos(Vec2(64.f * 6, 64.f * 18));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_2F_02)
		pObj->SetPos(Vec2(64.f * 23, 64.f * 11));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_pic)
		pObj->SetPos(Vec2(64.f * 23, 64.f * 33));


	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	// Gate 배치
	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 5 + 32, 64.f * 20));
	m_pGate01->SetScale(Vec2(64.f * 3, 64.f * 1));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 여기서는 ㅠㅠ 2번에서 들어가면 무조건 2층 2번 타일 상단으로 나오게만
	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 24, 64.f * 11));
	m_pGate02->SetScale(Vec2(64.f * 1, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);

	m_pGate03 = new CGate;
	m_pGate03->SetPos(Vec2(64.f * 24, 64.f * 33));
	m_pGate03->SetScale(Vec2(64.f * 1, 64.f * 6));
	AddObject(m_pGate03, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);

	// 그림
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 9 + 32, 64 * 6 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_01", L"texture\\미술관그림bmp\\2_01.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 13 + 32, 64 * 6));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_02", L"texture\\미술관그림bmp\\2_02.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	CObj* pic3 = new CPicture;
	pic3->SetPos(Vec2(64 * 17 + 32, 64 * 6 + 32));
	pic3->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_03", L"texture\\미술관그림bmp\\2_03.bmp"));
	AddObject(pic3, EOBJ_TYPE::PIC);

	CObj* pic4 = new CPicture;
	pic4->SetPos(Vec2(64 * 21 + 32, 64 * 6 + 32));
	pic4->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_04", L"texture\\미술관그림bmp\\2_04.bmp"));
	AddObject(pic4, EOBJ_TYPE::PIC);

	CObj* pic5 = new CPicture;
	pic5->SetPos(Vec2(64 * 21 + 32, 64 * 28 + 32));
	pic5->SetTexture(CResMgr::GetInst()->LoadTexture(L"2_011", L"texture\\미술관그림bmp\\2_011.bmp"));
	AddObject(pic5, EOBJ_TYPE::PIC);

	CObj* obj1 = new CPicture;
	obj1->SetPos(Vec2(64 * 13 + 32, 64 * 27));
	obj1->SetTexture(CResMgr::GetInst()->LoadTexture(L"m_05", L"texture\\M_objectbmp\\m_05.bmp"));
	AddObject(obj1, EOBJ_TYPE::PIC);

	CObj* standText3 = new CPicture;
	standText3->SetPos(Vec2(64 * 12 + 32, 64 * 16 + 32));
	standText3->SetTexture(CResMgr::GetInst()->LoadTexture(L"bm", L"texture\\ib\\bm.bmp"));
	AddObject(standText3, EOBJ_TYPE::PIC);

	CObj* standText4 = new CPicture;
	standText4->SetPos(Vec2(64 * 14 + 32, 64 * 16 + 32));
	standText4->SetTexture(CResMgr::GetInst()->LoadTexture(L"rm_stand", L"texture\\ib\\rm_stand.bmp"));
	AddObject(standText4, EOBJ_TYPE::PIC);

	CObj* standText5 = new CPicture;
	standText5->SetPos(Vec2(64 * 13 + 32, 64 * 18 + 32));
	standText5->SetTexture(CResMgr::GetInst()->LoadTexture(L"ym", L"texture\\ib\\ym.bmp"));
	AddObject(standText5, EOBJ_TYPE::PIC);

	// d오브젝트 & 텍스트 
	window1 = new CText;
	window1->SetPos(Vec2(64 * 5 + 32, 64 * 7));
	window1->SetScale(Vec2(30, 30));
	window1->SetUIScript(L"창밖은 밝다...");
	window1->SetTexture(CResMgr::GetInst()->LoadTexture(L"window", L"texture\\M_objectbmp\\창문.bmp"));
	AddObject(window1, EOBJ_TYPE::TEXT);

	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 9 + 32, 64 * 7 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetUIScript(L"\'신문지를 집는 귀부인\'");
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 13 + 32, 64 * 7 + 32));
	text2->SetScale(Vec2(20, 20));
	text2->SetUIScript(L"\'매달린 남자\'");
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 17 + 32, 64 * 7 + 32));
	text3->SetScale(Vec2(20, 20));
	text3->SetUIScript(L"\'??\'\n어려워서 읽을 수 없는 글자가 있다...");
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	CObj* text4 = new CText;
	text4->SetPos(Vec2(64 * 21 + 32, 64 * 7 + 32));
	text4->SetScale(Vec2(20, 20));
	text4->SetUIScript(L"\'염려\'\n");
	text4->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text4, EOBJ_TYPE::TEXT);

	CObj* text5 = new CText;
	text5->SetPos(Vec2(64 * 21 + 32, 64 * 29 + 32));
	text5->SetScale(Vec2(20, 20));
	text5->SetUIScript(L"\'테이블에 놓인??\'\n어려워서 읽을 수 없는 글자가 있다...");
	text5->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\텍스트2.bmp"));
	AddObject(text5, EOBJ_TYPE::TEXT);

	CObj* standText1 = new CText;
	standText1->SetPos(Vec2(64 * 13 + 32, 64 * 21 + 32));
	standText1->SetScale(Vec2(20, 20));
	standText1->SetUIScript(L"\'무개성\'");
	standText1->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명2", L"texture\\M_objectbmp\\설명2.bmp"));
	AddObject(standText1, EOBJ_TYPE::TEXT);

	CObj* standText2 = new CText;
	standText2->SetPos(Vec2(64 * 13 + 32, 64 * 30 + 32));
	standText2->SetScale(Vec2(20, 20));
	standText2->SetUIScript(L"\'지정석\'");
	standText2->SetTexture(CResMgr::GetInst()->LoadTexture(L"설명2", L"texture\\M_objectbmp\\설명2.bmp"));
	AddObject(standText2, EOBJ_TYPE::TEXT);


	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 9 + 32, 64 * 8 + 32));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetUIScript(L"\"잘 그렸구만~\"");
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m01_01", L"texture\\bmp_char\\2m01_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

		wstring str[3] = { L"\"내가 생각하기론.. 게르테나가 말하는 \n개성이라는건 표정이라고 생각해\""
			, L"\"그러니까 이 조각상들에겐 머리가 없는게 아닐까?\"", L"\"그렇게 생각하지 않아?\"" };
		subC2 = new CText;
		subC2->SetPos(Vec2(64 * 10 + 32, 64 * 15 + 32));
		subC2->SetScale(Vec2(30, 60));
		subC2->SetScriptList(str);
		subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m01_02_R", L"texture\\bmp_char\\2m01_02_R.bmp"));
		AddObject(subC2, EOBJ_TYPE::TEXT);

	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_2F_01::update()
{
	CStage::update();

	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_00);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_2F_02);
	}
	else if (((CGate*)m_pGate03)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_pic);
	}

	if (CStageMgr::GetInst()->IsSubCharOff() == false)
	{
		if (((CText*)subC2)->IsScriptOn())
		{
			subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m01_02_D", L"texture\\bmp_char\\2m01_02_D.bmp"));
		}
		else
			subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"2m01_02_R", L"texture\\bmp_char\\2m01_02_R.bmp"));
	}

	if (CStageMgr::GetInst()->IsMuseumEventOn())
	{
		if (pObj->GetPos().y <= 64.f * 13)
		{
			if (CStageMgr::GetInst()->IsWindow2Played() == false)
			{
				window1->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));

				CSound* window = CResMgr::GetInst()->FindSound(L"glass_ton2");
				window->Play();

				CObj* windowAni = new CPicture;
				windowAni->SetPos(Vec2(64 * 5 + 32, 64 * 7));
				windowAni->SetScale(Vec2(30, 30));
				windowAni->SetTexture(CResMgr::GetInst()->LoadTexture(L"window", L"texture\\M_objectbmp\\창문.bmp"));
				((CPicture*)windowAni)->PlayAnimation(L"M_WINDOW_HAND");
				AddObject(windowAni, EOBJ_TYPE::PIC);
				CStageMgr::GetInst()->TurnOnWindow2();
			}
		}
	}

}

void Stage_M_2F_01::render(HDC _dc)
{
	CStage::render(_dc);

}

void Stage_M_2F_01::Enter()
{
	init();
	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_M_2F_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
}

