#pragma once


class CObj;
class CTile;
class CPlayer;
class CTable;
class CTexture;
class CUI;
class CStage
{
private:
	vector<CObj*>	m_arrObj[(UINT)EOBJ_TYPE::END];

	UINT			m_iTileXCount;
	UINT			m_iTileYCount;

	CTexture* m_pVeilTex;
	CUI* pParentUI;

public:
	virtual void init() = 0;
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);

	virtual void Enter() = 0;
	virtual void Exit() = 0;


	// Get Set
public:
	UINT GetTileXCount() { return m_iTileXCount; }
	UINT GetTileYCount() { return m_iTileYCount; }


public:
	void AddObject(CObj* _pObj, EOBJ_TYPE _eType){m_arrObj[(UINT)_eType].push_back(_pObj);}
	const vector<CObj*>& GetObjects(EOBJ_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void CreateTile(UINT _iCol, UINT _iRow);
	void LoadTileFromFile(const wstring& _strRelativePath);
	CObj* GetPlayer();
	CTile* GetPosTile(UINT _row, UINT _col);
	void StageAdjustment();
	CTable* GetStageTable();
	bool IsTableExist();

	void DeleteScript();

	void Clear(EOBJ_TYPE _type);
	void Clear();

private:
	vector<CObj*>& GetObjectsRef(EOBJ_TYPE _eType) { return m_arrObj[(UINT)_eType]; }
	void render_tile(HDC _dc);
	void render_veil(HDC _dc);

public:
	CStage();
	virtual ~CStage();

	friend class CUIMgr;
};

