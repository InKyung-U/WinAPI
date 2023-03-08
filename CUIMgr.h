#pragma once

class CUI;

class CUIMgr
{
	SINGLE(CUIMgr);
private:
	list<CUI*>	m_queue;


	CUI*		m_pTargetUI;  // ���콺�� �ö� �ִ� UI, �켱������ �ڽ�UI �� �� ����
	CUI*		m_pFocusedUI; // �θ� UI �߿� �켱������ ���� ���� UI

	CUI*		m_pPressedUI; // ���콺�� �������� Ÿ�� UI
	CUI*		m_pUpUI;	  // ���콺�� �� �� Ÿ���̾��� UI

	Vec2		m_vMousePos;
	bool		m_bMouseLbtnDown;
	bool		m_bMouseLbtnUp;

	bool		m_bScriptOn;

public:
	void update();

	bool IsScriptOn() { return m_bScriptOn; }
	void ScriptTurnOn() { m_bScriptOn = true; }
	void ScriptTurnOff() { m_bScriptOn = false; }


private:
	CUI* GetTargetUI(CUI* _pUI);

};

