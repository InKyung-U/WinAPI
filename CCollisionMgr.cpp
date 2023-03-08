#include "pch.h"
#include "CCollisionMgr.h"

#include "CStageMgr.h"
#include "CStage.h"
#include "CObj.h"
#include "CCollider.h"


CCollisionMgr::CCollisionMgr()
	: m_arrCheck{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::update()
{
	for (UINT i = 0; i < MAX_LAYER; ++i)
	{
		for (UINT j = i; j < MAX_LAYER; ++j)
		{
			if (m_arrCheck[i] & (1 << j))
			{
				// i �� �ش��ϴ� EOBJ_TYPE ������Ʈ���, j �� �ش��ϴ�EOBJ_TYPE ������Ʈ�� ���� �浹 ����
				CStage* pCurStage = CStageMgr::GetInst()->GetCurStage();
				CollisionGroup(pCurStage->GetObjects((EOBJ_TYPE)i), pCurStage->GetObjects((EOBJ_TYPE)j));								
			}
		}
	}
}

void CCollisionMgr::CollisionGroup(const vector<CObj*>& _left, const vector<CObj*>& _right)
{
	CCollider* pLeftCol = nullptr;
	CCollider* pRightCol = nullptr;

	for (size_t i = 0; i < _left.size(); ++i)
	{
		pLeftCol = _left[i]->GetCollider();

		if (nullptr == pLeftCol)
			continue;

		for (size_t j = 0; j < _right.size(); ++j)
		{
			pRightCol = _right[j]->GetCollider();

			if (nullptr == pRightCol)
				continue;									


			// �� �浹ü�� ������ �浹�߾����� Ȯ��
			// �� �浹ü�� ���� ���̵� ����
			COLLIDER_ID ID;
			ID.iLeftID = pLeftCol->GetID();
			ID.iRightID = pRightCol->GetID();
			map<long long, bool>::iterator iter = m_mapColInfo.find(ID.id);

			// �� �浹ü�� ó�� �˻縦 �����ϰ� �ִ�.
			if (iter == m_mapColInfo.end())
			{
				m_mapColInfo.insert( make_pair(ID.id, false));
				iter = m_mapColInfo.find(ID.id);
			}
			

			// �� �浹ü�� �ϳ��� ���� �������� 
			bool bDead = pLeftCol->GetOwner()->IsDead() || pRightCol->GetOwner()->IsDead();

			// �浹 �˻�
			// �浹 ���̴�.
			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �����ӿ��� �浹 ���̾���.
				if (iter->second)
				{
					// �浹 ���̴�
					if (bDead)
					{
						// ���� �ϳ��� ���� �����̶��(������ ���� �浹 ������ �߻��ϴ� ������ ����)
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						m_mapColInfo.erase(iter);
					}	
					else
					{
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}

				// �������� �浹���� �ʰ� �־���.
				else
				{
					// �̹��� �� �浹 �����ߴ�.
					if (!bDead)
					{
						// �� �� �ϳ��� ���� �����̶�� �浹 ���� ��ü�� ���� �ʰ� �Ѵ�.
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}					
				}				
			}

			// �浹���� �ʰ� �ִ�.
			else
			{
				// ���� �����ӿ����� �浹 ���̾���.
				if (iter->second)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}				
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{	
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vRightPos = _pRightCol->GetFinalPos();

	Vec2 vLeftScale = _pLeftCol->GetScale();
	Vec2 vRightScal = _pRightCol->GetScale();

	float fDist = 0.f;

	// x �� �׽�Ʈ
	fDist = abs(vLeftPos.x - vRightPos.x);
	if (fDist > (vLeftScale.x / 2.f) + (vRightScal.x / 2.f))
		return false;

	// y �� �׽�Ʈ
	fDist = abs(vLeftPos.y - vRightPos.y);
	if (fDist > (vLeftScale.y / 2.f) + (vRightScal.y / 2.f))
		return false;

	return true;
}

void CCollisionMgr::CollisionCheck(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] |= (1 << iCol);
}

void CCollisionMgr::CollisionOff(EOBJ_TYPE _left, EOBJ_TYPE _right)
{
	UINT iCol = 0, iRow = 0;

	if ((UINT)_left > (UINT)_right)
	{
		iCol = (UINT)_left;
		iRow = (UINT)_right;
	}
	else
	{
		iCol = (UINT)_right;
		iRow = (UINT)_left;
	}

	m_arrCheck[iRow] &= ~(1 << iCol);
}
