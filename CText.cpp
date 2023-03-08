#include "pch.h"
#include "CText.h"
#include "CTexture.h"
#include "CUI.h"
#include "CUIMgr.h"
#include "CScript.h"
#include "CStageMgr.h"

CText::CText()
	: m_pTex(nullptr)
	, m_bTouchText(false)
	, m_bScriptExist(false)
	, pParentUI(nullptr)
	, m_sScript{}
	, m_bScriptSearchDone(false)
	, m_iScriptCount(1)
	, m_lscriptList{L""}
	, m_iScriptMaxCount(1)
{
	AddComponent(new CCollider);
}

CText::~CText()
{
}

void CText::update()
{
	if (m_bScriptExist)
	{
		if (m_iScriptMaxCount == 1 || m_iScriptMaxCount == m_iScriptCount)
		{
			if (KTAP(KEY::SPACE))
			{
				m_bScriptExist = false;
				CStageMgr::GetInst()->GetCurStage()->DeleteScript();
				CUIMgr::GetInst()->ScriptTurnOff();
				m_bScriptSearchDone = true;
				m_iScriptCount = 1;
			}
		}
		else if (m_iScriptMaxCount != m_iScriptCount)
		{
			if (KTAP(KEY::SPACE))
			{
				m_iScriptCount += 1;
				m_sScript = m_lscriptList[m_iScriptCount - 1];
				if (m_sScript.size() != 0)
				{
					pParentUI->SetUIScript(m_sScript);
				}
			}
		}
	}
	else if (m_bTouchText)
	{
		if (KTAP(KEY::SPACE))
		{
			pParentUI = nullptr;
			pParentUI = new CScript;
			m_bScriptSearchDone = false;
			if (m_iScriptMaxCount != 1)
			{
				m_sScript = m_lscriptList[m_iScriptCount - 1];
			}
			if (m_sScript.size() != 0)
			{
				pParentUI->SetUIScript(m_sScript);
			}
			CStageMgr::GetInst()->GetCurStage()->AddObject(pParentUI, EOBJ_TYPE::SCRIPTUI);
			m_bScriptExist = true;
			CUIMgr::GetInst()->ScriptTurnOn();
		}
	}
}

void CText::render(HDC _dc)
{
	UINT iWidth = m_pTex->Width();
	UINT iHeight = m_pTex->Height();
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, vRenderPos.x - iWidth / 2
		, vRenderPos.y - iHeight / 2
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0
		, iWidth, iHeight
		, RGB(255, 0, 255));

	render_component(_dc);
}

void CText::SetScale(Vec2 _scale)
{
	CObj::SetScale(_scale);
	GetCollider()->SetScale(_scale);
}

void CText::OnCollisionEnter(CObj* _pOtherObj)
{
	m_bTouchText = true;
}

void CText::OnCollisionExit(CObj* _pOtherObj)
{
	m_bTouchText = false;
}
