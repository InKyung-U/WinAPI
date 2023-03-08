#include "pch.h"
#include "CScript.h"
#include "CTexture.h"
#include "CCore.h"

#include "CResMgr.h"
#include "CUIMgr.h"

CScript::CScript()
	: m_pUITex()
	, m_bShowScript(false)
	, m_vScriptBoxPos{}
	, m_vScriptBoxScale{}
{
	m_pUITex = CResMgr::GetInst()->LoadTexture(L"sbox01", L"texture\\ib\\SBox01.bmp");
	CResMgr::GetInst()->LoadTexture(L"sbox02", L"texture\\ib\\SBox02.bmp");

	m_vScriptBoxPos = Vec2(150, 500);
	m_vScriptBoxScale = Vec2(724, 300);
}

CScript::~CScript()
{
}

void CScript::update()
{
	CUI::update();
}

void CScript::render(HDC _dc)
{
	Vec2 vWndPos = CCore::GetInst()->GetResolution();
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (CUIMgr::GetInst()->IsScriptOn())
	{
		BitBlt(_dc
			, vWndPos.x - m_pUITex->Width()
			, vWndPos.y - m_pUITex->Height()
			, m_pUITex->Width(), m_pUITex->Height()
			, m_pUITex->GetDC()
			, 0, 0
			, SRCCOPY);
	}
	RECT rectangle;
	SetRect(&rectangle
		, m_vScriptBoxPos.x, m_vScriptBoxPos.y
		, m_vScriptBoxPos.x + m_vScriptBoxScale.x
		, m_vScriptBoxPos.y + m_vScriptBoxScale.y);
	DrawText(_dc, m_sScript.c_str(), -1, &rectangle, DT_LEFT | DT_WORDBREAK | DT_EDITCONTROL	);
}

void CScript::MouseLbtnClicked(Vec2 _vMousePos)
{
}

