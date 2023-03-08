#include "pch.h"
#include "Stage_M_1F_01.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CText.h"

Stage_M_1F_01::Stage_M_1F_01()
	:m_pGate01(nullptr)
	,m_pGate02(nullptr)
	,m_pGate03(nullptr)


{
	LoadTileFromFile(L"tile\\m_1F_01");
}

Stage_M_1F_01::~Stage_M_1F_01()
{
}

void Stage_M_1F_01::init()
{

	POINT ptResolution = CCore::GetInst()->GetResolution();

	CObj* pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_00)
		pObj->SetPos(Vec2(64.f + 32, 896.f));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_02)
		pObj->SetPos(Vec2(64.f * 19, 64.f * 14));
	else if(CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::M_1F_03)
		pObj->SetPos(Vec2(64.f * 10, 64.f * 23));
	else if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());

	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(pObj->GetPos());
	StageAdjustment();

	m_pGate01 = new CGate;
	m_pGate01->SetPos(Vec2(64.f * 0 + 32, 64.f * 14));
	m_pGate01->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate01, EOBJ_TYPE::GATE);

	m_pGate02 = new CGate;
	m_pGate02->SetPos(Vec2(64.f * 20, 64.f * 14));
	m_pGate02->SetScale(Vec2(64.f, 64.f * 6));
	AddObject(m_pGate02, EOBJ_TYPE::GATE);

	m_pGate03 = new CGate;
	m_pGate03->SetPos(Vec2(64.f * 10, 64.f * 25));
	m_pGate03->SetScale(Vec2(64.f *6, 64.f * 1));
	AddObject(m_pGate03, EOBJ_TYPE::GATE);
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::GATE);


	// ������Ʈ
	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 10, 64 * 4));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"pic1", L"texture\\M_objectbmp\\�׸�1.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	wstring str[3] = { L"\'������� �Ը��׳��� ���迡! \n ���� �湮���ּż� ���� ����帳�ϴ�.\n �� �������� ���� -������ �Ը��׳� ��-�� \n �����ϰ� �ֽ��ϴ�.\'"
		, L"�Ը��׳��� ������ �׸� \n �⹦�ϰ� �Ƹ��ٿ� ��ǰ���� \n�ε� ������ ����ֽñ� �ٶ��ϴ�."
		, L"" };
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 10, 64 * 6 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetScriptList(str);
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text2", L"texture\\M_objectbmp\\�ؽ�Ʈ2.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	wstring str1[3] = { L"\'���� ���� ??\'", L"������� ���� �� ���� ���ڰ� �ִ�..", L"" };
	CObj* text2 = new CText;
	text2->SetPos(Vec2(64 * 5 + 32, 64 * 6 + 32));
	text2->SetScale(Vec2(40, 40));
	text2->SetScriptList(str1);
	text2->SetTexture(CResMgr::GetInst()->LoadTexture(L"text1", L"texture\\M_objectbmp\\�ؽ�Ʈ1.bmp"));
	AddObject(text2, EOBJ_TYPE::TEXT);

	
	CObj* pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 10, 64 * 14 + 32));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"fish", L"texture\\M_objectbmp\\fish.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	wstring str2[3] = { L"\'������ ?? \n ����� ������ �볳ġ �ʴ� \n �� ���踦 ??�ϱ� ���� ���� \n ĵ���� �ȿ� �� ���踦 ?�ߴ�\'"
			, L"������� ���� �� ���� ���ڰ� �ִ�..", L"" };
	CObj* text3 = new CText;
	text3->SetPos(Vec2(64 * 10, 64 * 18 + 32));
	text3->SetScale(Vec2(70, 30));
	text3->SetScriptList(str2);
	text3->SetTexture(CResMgr::GetInst()->LoadTexture(L"����1", L"texture\\M_objectbmp\\����1.bmp"));
	AddObject(text3, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsSubCharOff())
	{
		CObj* subC1 = new CText;
		subC1->SetPos(Vec2(64 * 10, 64 * 7));
		subC1->SetScale(Vec2(30, 60));
		subC1->SetUIScript(L"\"����Ѱ�..\"");
		subC1->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m01_01", L"texture\\bmp_char\\1m01_01.bmp"));
		AddObject(subC1, EOBJ_TYPE::TEXT);

		CObj* subC2 = new CText;
		subC2->SetPos(Vec2(64 * 10 + 32, 64 * 10));
		subC2->SetScale(Vec2(30, 60));
		subC2->SetUIScript(L"\"���� ���� �� ���Ƽ� ������....\"");
		subC2->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m01_02", L"texture\\bmp_char\\1m01_02.bmp"));
		AddObject(subC2, EOBJ_TYPE::TEXT);

		CObj* subC3 = new CText;
		subC3->SetPos(Vec2(64 * 6, 64 * 12));
		subC3->SetScale(Vec2(30, 60));
		subC3->SetUIScript(L"\"�� ��ǰ �� �ѹ� ���� �;���!\"");
		subC3->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m01_03", L"texture\\bmp_char\\1m01_03.bmp"));
		AddObject(subC3, EOBJ_TYPE::TEXT);

		CObj* subC4 = new CText;
		subC4->SetPos(Vec2(64 * 9+32, 64 * 19));
		subC4->SetScale(Vec2(30, 60));
		subC4->SetTexture(CResMgr::GetInst()->LoadTexture(L"1m01_04", L"texture\\bmp_char\\1m01_04.bmp"));
		AddObject(subC4, EOBJ_TYPE::TEXT);
	}

	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_M_1F_01::update()
{
	CStage::update();
	if (((CGate*)m_pGate01)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_00);
	}
	else if (((CGate*)m_pGate02)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_02);
	}
	else if (((CGate*)m_pGate03)->IsGateTouched())
	{
		ChangeStage(ESTAGE_TYPE::M_1F_03);
	}
}

void Stage_M_1F_01::render(HDC _dc)
{
	CStage::render(_dc);
}

void Stage_M_1F_01::Enter()
{
	CCamera::GetInst()->FadeIn(0.3f);

	init();
}

void Stage_M_1F_01::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
}
