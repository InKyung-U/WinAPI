#pragma once
#include "CKeyMgr.h"

class CTexture;

enum class ECAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	TURNOFF_HALF,
	TURNON,
	PLATERHIT,
	NONE,
};

struct tCamEffect
{
	ECAM_EFFECT eEffect;
	float		fAddTime;
	float		fEffectMaxTime;		
};


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2				m_vLookAt;
	Vec2				m_vDiff;	// �ػ� �߾� ������, ī�޶� �����ִ� �������� ���̰�
	CTexture*			m_pVeilTex;
	list<tCamEffect>	m_EffectQueue;	// ī�޶� ȿ�� ť

	float				m_second;

public:
	void init();
	void update();
	void render(HDC _dc);
	
public:
	Vec2 GetRenderPos(Vec2 _vRealPos){return _vRealPos - m_vDiff;}
	Vec2 GetRealPos(Vec2 _vRenderPos) {return _vRenderPos + m_vDiff;}
	Vec2 GetLookAtPos() { return m_vLookAt; }
	void SetLookAtPos(Vec2 _pos) { m_vLookAt = _pos; }
	void AddLookAtPos(Vec2 _pos) { m_vLookAt += _pos; }
	void CameraAdjustment(UINT _tileWidth, UINT _tileHeight);
	bool IsCameraMove(UINT _stageWidth, UINT _stageHeight, KEY _pressedKey, Vec2 _playerPos);


	void FadeIn(float _fTime/*ȿ�� �ð�*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::FADE_IN;
		effect.fEffectMaxTime = _fTime;
		effect.fAddTime = 0.f;

		m_EffectQueue.push_back(effect);
	}

	void FadeOut(float _fTime/*ȿ�� �ð�*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::FADE_OUT;
		effect.fEffectMaxTime = _fTime;
		effect.fAddTime = 0.f;

		m_EffectQueue.push_back(effect);
	}

	void TurnOffHalf(float _fTime/*ȿ�� �ð�*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::TURNON;
		effect.fEffectMaxTime = _fTime;
		effect.fAddTime = 0.f;

		m_EffectQueue.push_back(effect);
	}

	void TurnON(float _fTime/*ȿ�� �ð�*/)
	{
		tCamEffect effect = {};
		effect.eEffect = ECAM_EFFECT::TURNOFF_HALF;
		effect.fEffectMaxTime = _fTime;
		effect.fAddTime = 0.f;

		m_EffectQueue.push_back(effect);
	}

	// void Vibration(float _Range/*����*/, float _fTime/*���� �����ð�*/, float _fSpeed);

};

