#include "pch.h"
#include "CEventMgr.h"

#include "CStageMgr.h"
#include "CStage.h"

#include "CObj.h"
#include "CFSM.h"

CEventMgr::CEventMgr()
{

}

CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// Dead Object 삭제
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		assert(m_vecDead[i]);
		delete m_vecDead[i];
	}
	m_vecDead.clear();


	// Event 처리
	bool bChangeStage = false;

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		switch (m_vecEvent[i].eType)
		{
		case EEVENT_TYPE::CREATE_OBJ:
			// lParam : Object Adress, wParam : Object Type
		{
			CObj* pNewObj = (CObj*)m_vecEvent[i].lParam;
			EOBJ_TYPE eType = (EOBJ_TYPE)m_vecEvent[i].wParam;

			CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
			pCurStage->AddObject(pNewObj, eType);
		}
			break;

		case EEVENT_TYPE::DELETE_OBJ:
			// lParam : Object Adress
		{
			CObj* pDeletObj = (CObj*)m_vecEvent[i].lParam;
			pDeletObj->SetDead();
			m_vecDead.push_back(pDeletObj);
		}
			break;
		case EEVENT_TYPE::STAGE_CHANGE:
			// lParam : Next Stage Enum		
			CStageMgr::GetInst()->ChangeStage((ESTAGE_TYPE)m_vecEvent[i].lParam);		
			bChangeStage = true;
			break;

		case EEVENT_TYPE::CHANGE_AI_STATE:
		{
			// lParam : FSM Adress, wParam : Next State Type
			CFSM* pFSM = (CFSM*)m_vecEvent[i].lParam;
			EMON_STATE eNextState = (EMON_STATE)m_vecEvent[i].wParam;
			pFSM->ChangeState(eNextState);
		}
			break;
		}	


		// 이벤트 중에 Stage 변경 이벤트가 있었다면,
		// 나머지 이벤트는 다 무시하고 종료
		if (bChangeStage)
		{
			break;
		}
	}

	m_vecEvent.clear();
}