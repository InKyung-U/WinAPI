#pragma once


#define SINGLE(type)	public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
						type();\
						~type();

#define DS CTimeMgr::GetInst()->GetDS()

#define KPRESSED(key) KEY_STATE::PRESSED == CKeyMgr::GetInst()->GetKeyState(key)
#define KTAP(key)     KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(key)
#define KAWAY(key)    KEY_STATE::AWAY == CKeyMgr::GetInst()->GetKeyState(key)
#define KNONE(key)    KEY_STATE::NONE == CKeyMgr::GetInst()->GetKeyState(key)

#define PI 3.14159289f

#define MAX_LAYER 32

#define TILE_SIZE 64

#define CLONE(type) virtual type* Clone()override {return new type(*this);}

enum class ESTAGE_TYPE
{
	TOOL,
	TITLE,
	STARTANIMATION,
	STARTSCRIPT,
	ENDSTAGE,
	START,
	GAMEOVER,
	PLAY_01,
	PLAY_02,
	M_1F_00,
	M_1F_01,
	M_1F_01_02,
	M_1F_02,
	M_1F_03,
	M_1F_pic,
	M_2F_01,
	M_2F_02,
	B_00,
	B_01,
	B_02,
	B_03,
	B_04,
	G_01,
	G_02,
	G_03,

	MENU,
	EXIT,

	END,
};

enum class EOBJ_TYPE
{
	DEFAULT,
	TILE,
	PIC,
	TEXT,
	TABLE,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	FORCE,
	BLOCK,
	GATE,
	DOOR,
	HAND,

	VEIL = 29,
	SCRIPTUI = 30,
	UI = 31,
	END = 32
};

enum class EEVENT_TYPE
{
	CREATE_OBJ, // lParam : Object Adress, wParam : Object Type
	DELETE_OBJ,
	STAGE_CHANGE, // lParam : Next Stage Enum
	CHANGE_AI_STATE, // lParam : FSM Adress, wParam : Next State Type

	END,
};

enum class ECOM_TYPE
{
	COLIIDER,
	ANIMATOR,
	FSM,
	MOVEMENT,
	END,
};

enum class EMON_STATE
{
	MON_IDLE,
	MON_TRACE,
	MON_ATTACK,
	MON_DEAD,
};