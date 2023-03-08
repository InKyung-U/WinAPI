#include "pch.h"
#include "CUI.h"

#include "CKeyMgr.h"


CUI::CUI()
	: m_pParent(nullptr)
	, m_bMouseOn(false)
	, m_bMouseLbtnPressed(false)
	, m_ClickDelegate{}
{
}

CUI::CUI(const CUI& _origin)
	: CObj(_origin)
	, m_pParent(nullptr)	
	, m_bMouseOn(false)
	, m_bMouseLbtnPressed(false)
	, m_ClickDelegate(_origin.m_ClickDelegate)
{
	// _origin.m_vecChildUI; -> m_vecChildUI;
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChildUI(_origin.m_vecChildUI[i]->Clone());		
	}
}

CUI::~CUI()
{
	Safe_Del_Vec(m_vecChildUI);
}

void CUI::DragDrop_update()
{
	if (IsLbtnPressed())
	{
		// ���� ���콺 ��ġ
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();

		// ���� ���콺 ��ġ���� UI �� �������� ��ǥ�� ���� ���̰��� ����
		Vec2 vDiff = vMousePos - GetLbtnPressedPos();

		// ���̰� ��ŭ ������
		SetPos(GetPos() + vDiff);

		// ���콺�� ���� ��ġ�� ���� ���콺 ��ġ�� ����
		SetLbtnPressedPos(vMousePos);
	}
}

void CUI::update()
{
	Vec2 vPos = GetPos();

	if (nullptr == m_pParent)
	{
		m_vFinalPos = vPos;
	}
	else
	{
		m_vFinalPos = vPos + m_pParent->GetFinalPos();
	}

	// MouseOn Check
	m_bMouseOn = IsMouseOn(CKeyMgr::GetInst()->GetMousePos());

	// Mouse Up Check
	if (KAWAY(KEY::LBTN))
	{
		m_bMouseLbtnPressed = false;
	}


	// ChildUI update
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::render(HDC _dc)
{
	Vec2 vFinalPos = GetFinalPos();
	Vec2 vScale = GetScale();

	Rectangle(_dc
		, int(vFinalPos.x)
		, int(vFinalPos.y)
		, int(vFinalPos.x + vScale.x)
		, int(vFinalPos.y + vScale.y));

	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}


bool CUI::IsMouseOn(Vec2 _vMouseRealPos)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (vPos.x <= _vMouseRealPos.x && _vMouseRealPos.x <= (vPos.x + vScale.x)
		&& vPos.y <= _vMouseRealPos.y && _vMouseRealPos.y <= (vPos.y + vScale.y))
	{
		return true;
	}

	return false;
}


void CUI::MouseLbtnClicked(Vec2 _vMousePos)
{
	if (nullptr != m_ClickDelegate.pStage && nullptr != m_ClickDelegate.pMemFunc)
	{
		(m_ClickDelegate.pStage->*m_ClickDelegate.pMemFunc)();
	}
}
