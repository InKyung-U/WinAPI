#include "pch.h"
#include "CStartScript.h"

#include "CCore.h"
#include "CTexture.h"
#include "CScript.h"

#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CStageMgr.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"


CStartScript::CStartScript()
	: m_pBackImg(nullptr)
	, m_iScriptCount(0)
	, m_fAddTime(0.f)
{
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	m_pBackImg = CResMgr::GetInst()->CreateTexture(L"blackBackTex", (UINT)vResolution.x, (UINT)vResolution.y);

	m_pScript1 = L"정오가 조금 지났을 무렵 \n회색빛 하늘 아래 ...";
}

CStartScript::~CStartScript()
{
}

void CStartScript::init()
{
}

void CStartScript::update()
{
	CStage::update();

	m_fAddTime += DS;

	if (4.f < m_fAddTime)
	{
		if (KTAP(KEY::SPACE))
			m_iScriptCount++;
		if (m_iScriptCount == 1)
			m_pScript1 = L"이브와 이브의 부모님은\n미술관으로 향했습니다.";
		if (m_iScriptCount == 2)
			m_pScript1 = L"\"잊은 물건은 없니? 이브\"";
		if (m_iScriptCount == 3)
			m_pScript1 = L"\"그래, 손수건은 챙겼니?\n그 생일날 준 거 말이야\"";
		if (m_iScriptCount == 4)
			m_pScript1 = L"\"주머니속에 잘 넣어두렴,\n잃어버리지 않게 말이야\"";
		if (m_iScriptCount == 5)
			ChangeStage(ESTAGE_TYPE::STARTANIMATION);
	}
}

void CStartScript::render(HDC _dc)
{
	CStage::render(_dc);

	BitBlt(_dc
		, 0, 0
		, m_pBackImg->Width()
		, m_pBackImg->Height()
		, m_pBackImg->GetDC()
		, 0, 0
		, SRCCOPY);

	if (4.f < m_fAddTime)
	{
		RECT rectangle;
		SetRect(&rectangle, 200, 300, 800, 500);
		DrawText(_dc, m_pScript1.c_str(), -1, &rectangle, DT_CENTER | DT_WORDBREAK | DT_EDITCONTROL);
	}
}

void CStartScript::Enter()
{
	CStageMgr::GetInst()->Setbgm(L"opening");
	CCamera::GetInst()->FadeIn(4.f);
	init();
}

void CStartScript::Exit()
{

}
