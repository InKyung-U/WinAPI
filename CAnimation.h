#pragma once


class CTexture;

struct tAnimFrm
{
	Vec2	vLeftTop;
	Vec2	vSize;
	Vec2	vOffset;
	float	fDuration;
};

class CAnimator;

class CAnimation
{
private:
	CAnimator*			m_pAnimator;
	wstring				m_strName;

	CTexture*			m_pAtlas;
	vector<tAnimFrm>	m_vecFrm;
	int					m_iCurIdx;
	float				m_fAddTime;
	bool				m_bFinish;

public:
	const wstring& GetName() { return m_strName; }

public:
	void update();
	void render(HDC _dc);

	void Create(const wstring& _strName, CTexture* _pAtlasTex
		, Vec2 _vLeftTop, Vec2 _vSize, float _fXDistance, float _fDuration, UINT _iFrmCount);

	CObj* GetOwner();
	bool IsFinish() { return m_bFinish; }
	void Reset()
	{
		m_iCurIdx = 0;
		m_fAddTime = 0.f;
		m_bFinish = false;
	}

	void Save(const wstring& _strRelativeFolderPath);
	void Load(const wstring& _strRelativeFilePath);

	CAnimation* Clone() { return new CAnimation(*this); }

	void CreateByLoadFromFile(CAnimation* _cAnimation);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

