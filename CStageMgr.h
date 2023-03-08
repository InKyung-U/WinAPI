#pragma once
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CKeyMgr.h"

class CStage;
class CObj;
class CSound;
class CStageMgr
{
	SINGLE(CStageMgr);
private:
	CStage* m_arrStage[(UINT)ESTAGE_TYPE::END];	// 모든 스테이지
	CStage* m_pCurStage;
	ESTAGE_TYPE m_pCurStageType;
	ESTAGE_TYPE m_pPrevStageType;
	UINT m_pPrevDoorNUM;

	Vec2 m_vTablePos;
	Vec2 m_vPlayerPos;

	bool m_bMStageSubCharOff;
	bool m_bRose;

	bool m_bHaveBlueKey;
	bool m_bHaveGreenKey;
	bool m_bMuseumKey;
	bool m_bMuseumEventOn;
	bool m_bMStageVeilOn;

	bool m_bRedBall;
	bool m_bWindow1;
	bool m_bWindow2;

	bool m_bAntPic;
	bool m_bAntPicPutTile;
	UINT m_iAntPicCount;

	bool m_bBlueDoorOpen;
	bool m_bGreenDoorOpen;

	bool m_bPlayerHit;
	bool m_bMonsterBroken;
	bool m_bMonsterBrokenSound;

	bool m_bEventAnimationOn;
	UINT m_iRoseCount;
	bool m_bHandPopUp;

	CSound* pNewSound;
	float m_fSoundMaxTime;
	float m_fSoundAddTime;

	KEY	m_kPlayerKeyState;

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CStage* GetCurStage() { return m_pCurStage; }
	ESTAGE_TYPE GetPrevStageType() { return m_pPrevStageType; }
	ESTAGE_TYPE GetCurStageType() { return m_pCurStageType; }

	CObj* GetPlayer();
	void SetPrevDoor(UINT _door) { m_pPrevDoorNUM = _door; }
	UINT GetPrevDoor() { return m_pPrevDoorNUM; }

	void SetTablePos(Vec2 _pos) { m_vTablePos = _pos; }
	Vec2 GetTablePos() { return m_vTablePos; }
	Vec2 GetPlayerPos() { return m_vPlayerPos; }
	void SetPlayerPos(Vec2 _pos) { m_vPlayerPos = _pos; }

	void SaveKeyState(KEY _state) { m_kPlayerKeyState = _state; }
	KEY GetKeyState() { return m_kPlayerKeyState; }


	//UI
	UINT GetRoseCount() { return m_iRoseCount; }
	void SetRoseCount(UINT _count) { m_iRoseCount = _count; }
	void SubRoseCount() { --m_iRoseCount; }

	// Player Hit
	bool IsPlayerHit() { return m_bPlayerHit; }
	void TurnOnPlayerHit() { m_bPlayerHit = true; }
	void TurnOffPlayerHit() { m_bPlayerHit = false; }

	// M stage
	bool IsSubCharOff() { return m_bMStageSubCharOff; }
	void SubCharTurnOff() { m_bMStageSubCharOff = true; }
	bool IsMuseumSearchDone() { return m_bMuseumKey; }
	void MuseumSearchDone() { m_bMuseumKey = true; }
	bool IsMStageVeilOn() { return m_bMStageVeilOn; }
	void TrunOnMStageVeil() { m_bMStageVeilOn = true; }
	bool IsMuseumEventOn() { return m_bMuseumEventOn; }
	void TurnMuseumEventOn() { m_bMuseumEventOn = true; }

	// M stage PicAni
	bool IsRedBallPlayed() { return m_bRedBall; }
	void TurnOnRedBall() { m_bRedBall = true; }
	bool IsWindow1Played() { return m_bWindow1; }
	void TurnOnWindow1() { m_bWindow1 = true; }
	bool IsWindow2Played() { return m_bWindow2; }
	void TurnOnWindow2() { m_bWindow2 = true; }

	// B stage
	bool IsPlayerHaveRose() { return m_bRose; }
	void SetRoseTurnTrue() { m_bRose = true; }	
	bool IsHaveBlueKey() { return m_bHaveBlueKey; }
	void TurnOnBlueKey() { m_bHaveBlueKey = true; }
	void TurnOffBlueKey() { m_bHaveBlueKey = false; }
	bool IsBlueDoorOpen() { return m_bBlueDoorOpen; }
	void OpenBlueDoor() { m_bBlueDoorOpen = true; }

	bool IsGreenDoorOpen() { return m_bGreenDoorOpen; }
	void OpenGreenDoor() { m_bGreenDoorOpen = true; }
	// G stage
	bool IsHaveGreenKey() { return m_bHaveGreenKey; }
	void TurnOnGreenKey() { m_bHaveGreenKey = true; }
	void TurnOffGreenKey() { m_bHaveGreenKey = false; }

	bool IsEventAnimationOn() { return m_bEventAnimationOn; }
	void TurnOnEventAnimation() { m_bEventAnimationOn = true; }
	void TurnOffEventAnimation() { m_bEventAnimationOn = false; }
	bool IsMonsterBroken() { return m_bMonsterBroken; }
	void TurnOnMonsterBroken() { m_bMonsterBroken = true; }
	bool IsHandPopUp() { return m_bHandPopUp; }
	void TurnOnHandPopUp() { m_bHandPopUp = true; }
	bool HaveAntPic() { return m_bAntPic; }
	void TurnOnAntPic() { m_bAntPic = true; }
	void TurnOffAntPic() { m_bAntPic = false; }
	bool IsAntPicPutTile() { return m_bAntPicPutTile; }
	void TurnOnAntPicPutTile() { m_bAntPicPutTile = true; }
	void SubAntPicCount() { m_iAntPicCount--; }
	UINT returnAntPicCount() { return m_iAntPicCount; }
	bool IsMonsterBrokenSoundPlayed() { return m_bMonsterBrokenSound; }
	void TurnOnMonsterBrokenSound() { m_bMonsterBrokenSound = true; }

	// Sound
	void Setbgm(wstring _str);
	void SetbgmDecrescendo(float _maxTime) { m_fSoundMaxTime = _maxTime; }

private:
	void ChangeStage(ESTAGE_TYPE _eNextStage);

	friend class CEventMgr;
};

