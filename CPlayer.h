#pragma once

#include "CObj.h"

#include "CResMgr.h"
#include "CSoundMgr.h"
#include "CSound.h"

class CTexture;
class CSound;

enum class EBULLET_TYPE
{
	NORMAL,
	GUIDED,	
	ENERGY,
};

class CPlayer
	: public CObj
{
private:	
	float			m_fSpeed;
	CTexture*		m_pTex;
	EBULLET_TYPE	m_eBulletType;
	KEY				m_kPlayerKeyState;

	float			m_fAddSecond;
	float			m_fMaxHitSecond;
	float			m_fAddHitSecond;

	CSound* pNewSound;

public:
	void update() override;	
	void render(HDC _dc) override;
	void OnCollision(CObj* _pOtherObj) override;

	void stopFootSound() { pNewSound->Stop(); }

	KEY GetPlayerKeyState() { return m_kPlayerKeyState; }
	bool CanIMoveNextTile(Vec2 _pos);

private:
	void Shoot();

public:
	CLONE(CPlayer);

public:
	CPlayer();
	~CPlayer();
};

