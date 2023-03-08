#pragma once

class CObj;
class CCollider;

union COLLIDER_ID
{
	struct {
		UINT iLeftID;
		UINT iRightID;
	};
	long long id;
};

class CCollisionMgr
{
	SINGLE(CCollisionMgr);
private:
	UINT					m_arrCheck[MAX_LAYER];
	map<long long, bool>	m_mapColInfo;


public:
	void update();

private:
	void CollisionGroup(const vector<CObj*>& _left, const vector<CObj*>& _right);
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);


public:
	void CollisionCheck(EOBJ_TYPE _left, EOBJ_TYPE _right);
	void CollisionOff(EOBJ_TYPE _left, EOBJ_TYPE _right);
};

