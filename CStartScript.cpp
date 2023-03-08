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

	m_pScript1 = L"������ ���� ������ ���� \nȸ���� �ϴ� �Ʒ� ...";
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
			m_pScript1 = L"�̺�� �̺��� �θ����\n�̼������� ���߽��ϴ�.";
		if (m_iScriptCount == 2)
			m_pScript1 = L"\"���� ������ ����? �̺�\"";
		if (m_iScriptCount == 3)
			m_pScript1 = L"\"�׷�, �ռ����� ì���?\n�� ���ϳ� �� �� ���̾�\"";
		if (m_iScriptCount == 4)
			m_pScript1 = L"\"�ָӴϼӿ� �� �־�η�,\n�Ҿ������ �ʰ� ���̾�\"";
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
