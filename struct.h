#pragma once


struct Vec2
{
public:
	float x;
	float y;


public:
	bool IsZero()
	{
		if (x == 0.f && y == 0.f)
		{
			return true;
		}

		return false;
	}

	float GetDistance(Vec2 _vOther)
	{
		return (float)sqrtf(powf(x - _vOther.x, 2.f) + powf(y - _vOther.y, 2.f));
	}

	float GetLength()
	{
		return sqrtf(x * x + y * y);
	}

	Vec2& Normalize()
	{
		float fDist = (float)sqrt(pow((double)x, 2.) + pow((double)y, 2.));
		x /= fDist;
		y /= fDist;

		return *this;
	}

	float Dot(Vec2 _vOther)
	{
		return x* _vOther.x + y * +_vOther.y;
	}


public:
	// ========
	// operator
	// ========
	Vec2 operator + (float _f)
	{
		return Vec2(x + _f, y + _f);
	}

	void operator += (float _f)
	{
		x += _f;
		y += _f;
	}

	void operator += (Vec2 _v)
	{
		x += _v.x;
		y += _v.y;
	}

	void operator -= (Vec2 _v)
	{
		x -= _v.x;
		y -= _v.y;
	}

	void operator = (const POINT& _pt)
	{
		x = (float)_pt.x;
		y = (float)_pt.y;
	}

	Vec2 operator - ()
	{
		return Vec2(-x, -y);
	}


	Vec2 operator - (float _f)
	{
		return Vec2(x - _f, y - _f);
	}

	Vec2 operator * (float _f)
	{
		return Vec2(x * _f, y * _f);
	}

	void operator *= (float _f)
	{
		x *= _f;
		y *= _f;
	}

	Vec2 operator / (float _f)
	{
		assert(_f);

		return Vec2(x / _f, y / _f);
	}

	Vec2 operator + (const Vec2& _other)
	{
		return Vec2(x + _other.x, y + _other.y);
	}

	Vec2 operator - (const Vec2& _other)
	{
		return Vec2(x - _other.x, y - _other.y);
	}

	Vec2 operator * (const Vec2& _other)
	{
		return Vec2(x * _other.x, y * _other.y);
	}

	Vec2 operator / (const Vec2& _other)
	{
		assert(_other.x); assert(_other.y);
		return Vec2(x / _other.x, y / _other.y);
	}

	bool operator == (const Vec2 _other)
	{
		if (x == _other.x && y == _other.y)
			return true;
		else
			return false;
	}

	void operator /= (float _f)
	{
		assert(_f); 

		x /= _f;
		y /= _f;
	}





public:
	Vec2()
		: x(0.f)
		, y(0.f)
	{}

	Vec2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vec2(long _x, long _y)
		: x(float(_x))
		, y(float(_y))
	{}

	Vec2(int _x, int _y)
		: x(float(_x))
		, y(float(_y))
	{}

	Vec2(const POINT& _pt)
		: x(float(_pt.x))
		, y(float(_pt.y))
	{}
};


struct tEventInfo
{
	EEVENT_TYPE eType;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};


struct tMonInfo
{
	wstring strMonName;		// 몬스터 이름
	float	m_fMaxHP;		// 최대 체력
	float	m_fCurHP;		// 현재 체력
	float	m_fAtt;			// 공격력
	float	m_fDetectRange;	// 플레이어 탐지 범위
	float	m_fAttRange;	// 공격 가능 범위
	float	m_fSpeed;
};