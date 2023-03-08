#include "pch.h"
#include "CState_Trace.h"

#include "CStageMgr.h"
#include "CTimeMgr.h"

CState_Trace::CState_Trace()
	: CState(EMON_STATE::MON_TRACE)
{
}

CState_Trace::~CState_Trace()
{
}

// �������·� ��ȯ�Ǵ� ù ������ ȣ��
void CState_Trace::Enter()
{
	// ���͸� �����ͼ� ���� �ִϸ��̼� ��� ȣ�� ���
}


void CState_Trace::update()
{
	if (DeadCheck())
		return;


	// �÷��̾ �i�ư���.

	// ���� ���¸� �������� ���͸� �˾Ƴ���.
	CMonster* pMonster = GetOwnerMonster();

	// ������ ���� ��ġ�� Ž�������� �˾Ƴ���.
	Vec2 vMonPos = pMonster->GetPos();
	float fDetectRange = pMonster->GetMonInfo().m_fDetectRange;
	float fSpeed = pMonster->GetMonInfo().m_fSpeed;

	// �÷��̾ �˾Ƴ���.
	CObj* pPlayer = CStageMgr::GetInst()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ���Ϳ��� �÷��̾ ���� ������ �˾Ƴ���.
	Vec2 vDir = vPlayerPos - vMonPos;
	vDir.Normalize();

	// ���͸� �÷��̾ ���ؼ� �̵���Ų��.
	if (abs(vDir.x) > abs(vDir.y))
	{
		if (vDir.x > 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_R");
				vMonPos.x += vDir.x * fSpeed * DS;
			}
			else
			{
			}
		}
		else if (vDir.x <= 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_L");
				vMonPos.x += vDir.x * fSpeed * DS;
			}
			else
			{
			}
		}
	}
	else if(abs(vDir.x) <= abs(vDir.y))
	{
		if (vDir.y > 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y + 32)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_UD");
				vMonPos.y += vDir.y * fSpeed * DS;
			}
			else
			{
			}
		}
		else if (vDir.y <= 0)
		{
			if (pMonster->CanIMoveNextTile(Vec2(vMonPos.x, vMonPos.y - 32)))
			{
				pMonster->ChangeAnimation(L"RMANE_WALK_UD");
				vMonPos.y += vDir.y * fSpeed * DS;
			}
			else
			{
			}
		}
	}
	//vMonPos += vDir * fSpeed * DS;
	pMonster->SetPos(vMonPos);
	//if (vDir.y < 0) // ++
	//{
	//	pMonster->ChangeAnimation(L"RMANE_WALK_UD");
	//
	//	if(vDir.x < 0)
	//		pMonster->ChangeAnimation(L"RMANE_WALK_L");
	//}

	

	// ���� �÷��̾ ���ݹ��� ������ ������ ==> ���ݻ��·� ����

	// �÷��̾ Ž������ �̻����� �����
	// Ž�� �ߴ� ==> ������������ �ǵ��ư� ==> Idle

	
	// ���� ������ HP �� 0 ���϶��
	// ==> Dead

}
