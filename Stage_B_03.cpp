#include "pch.h"
#include "Stage_B_03.h"

#include "CCollisionMgr.h"
#include "CStageMgr.h"
#include "CResMgr.h"

#include "CCore.h"
#include "CPlayer.h"
#include "CGate.h"
#include "CPicture.h"
#include "CText.h"
#include "CUI.h"
#include "CPanel.h"
#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

Stage_B_03::Stage_B_03()
	: m_pObj(nullptr)
	, BlueKey(nullptr)
	, pic2(nullptr)
{
	LoadTileFromFile(L"tile\\b_03");
}

Stage_B_03::~Stage_B_03()
{
}

void Stage_B_03::init()
{
	POINT ptResolution = CCore::GetInst()->GetResolution();

	m_pObj = new CPlayer;

	if (CStageMgr::GetInst()->GetPrevStageType() == ESTAGE_TYPE::MENU)
		m_pObj->SetPos(CStageMgr::GetInst()->GetPlayerPos());
	else
		m_pObj->SetPos(Vec2(64.f * 10 + 32, 64.f * 11));
	m_pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(m_pObj, EOBJ_TYPE::PLAYER);

	CCamera::GetInst()->SetLookAtPos(m_pObj->GetPos());
	StageAdjustment();

	CObj* pic1 = new CPicture;
	pic1->SetPos(Vec2(64 * 10 + 32, 64 * 4 + 32));
	pic1->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_face", L"texture\\b_bmp\\b_face.bmp"));
	AddObject(pic1, EOBJ_TYPE::PIC);

	pic2 = new CPicture;
	pic2->SetPos(Vec2(64 * 10 + 32, 64 * 4 + 15));
	pic2->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_face1", L"texture\\b_bmp\\b_face1.bmp"));
	AddObject(pic2, EOBJ_TYPE::PIC);

	wstring str1[3] = {L"\'그 장미가 ??를 잃어갈 때 그대도 ??된다\'",L"어려워서 읽을 수 없는 글자가 있다.",L""};
	CObj* text1 = new CText;
	text1->SetPos(Vec2(64 * 10 + 32, 64 * 6 + 32));
	text1->SetScale(Vec2(20, 20));
	text1->SetScriptList(str1);
	text1->SetTexture(CResMgr::GetInst()->LoadTexture(L"text1", L"texture\\M_objectbmp\\텍스트1.bmp"));
	AddObject(text1, EOBJ_TYPE::TEXT);

	if (!CStageMgr::GetInst()->IsHaveBlueKey())
	{
		wstring str2[3] = { L"뭔가 떨어져 있다...",L"파란 열쇠를 얻었다.",L"" };

		BlueKey = new CText;
		BlueKey->SetPos(Vec2(64 * 10 + 32, 64 * 8 + 32));
		BlueKey->SetScale(Vec2(15, 30));
		BlueKey->SetScriptList(str2);
		BlueKey->SetTexture(CResMgr::GetInst()->LoadTexture(L"b_key", L"texture\\b_bmp\\b_key.bmp"));
		AddObject(BlueKey, EOBJ_TYPE::TEXT);
	}
	CCollisionMgr::GetInst()->CollisionCheck(EOBJ_TYPE::PLAYER, EOBJ_TYPE::TEXT);

}

void Stage_B_03::update()
{
	CStage::update();

	Vec2 vPos = m_pObj->GetPos();
	if (64 * 10 <= vPos.x && vPos.x <= 64 * 11 && 64 * 11 <= vPos.y && vPos.y <= 64 * 12)
	{
		if (KTAP(KEY::SPACE))
		{
			if (((CPlayer*)m_pObj)->GetPlayerKeyState() == KEY::DOWN)
			{
				CSound* doorEnter = CResMgr::GetInst()->FindSound(L"door_open");
				doorEnter->Play();
				ChangeStage(ESTAGE_TYPE::B_04);
			}
		}
	}
	if (((CText*)BlueKey)->IsScriptSearchDone())
	{
		if (!CStageMgr::GetInst()->IsHaveBlueKey())
		{
			CStageMgr::GetInst()->TurnOnBlueKey();
			BlueKey->SetScale(Vec2(0, 0));
			BlueKey->SetTexture(CResMgr::GetInst()->LoadTexture(L"nullbmp", L"texture\\nullbmp.bmp"));
			CSound* KeyGet = CResMgr::GetInst()->FindSound(L"item_get");
			KeyGet->Play();
			((CPicture*)pic2)->PlayAnimation(L"B_SMILE");
		}
	}
}

void Stage_B_03::render(HDC _dc)
{
	CStage::render(_dc);


}

void Stage_B_03::Enter()
{
	init();

	CSound* doorClose = CResMgr::GetInst()->FindSound(L"door_close");
	doorClose->Play();

	if (CStageMgr::GetInst()->IsPlayerHaveRose())
	{
		// UI 만들기
		Vec2 vScale = Vec2(120, 160);
		Vec2 vPos = Vec2(0.f, 0.f);
		CUI* pParentUI = nullptr;
		// UI 1
		pParentUI = new CPanel;
		pParentUI->SetPos(vPos);
		pParentUI->SetScale(vScale);
		AddObject(pParentUI, EOBJ_TYPE::UI);
	}

	CCamera::GetInst()->FadeIn(0.3f);

}

void Stage_B_03::Exit()
{
	Clear(EOBJ_TYPE::PLAYER);
	Clear(EOBJ_TYPE::GATE);
	Clear(EOBJ_TYPE::PIC);
	Clear(EOBJ_TYPE::TEXT);
	Clear(EOBJ_TYPE::SCRIPTUI);
}
