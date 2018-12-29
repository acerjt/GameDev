#pragma once
#include "GameObject.h"
#include "MorningStar.h"
#include "Weapons.h"
#include "Dagger.h"
#include "Boomerang.h"
#include "Axe.h"
#include "HolyWater.h"
#include "StopWatch.h"

#define SIMON_WALKING_SPEED				0.11f
#define SIMON_WALKING_CASTLE_SPEED		0.04f 
#define SIMON_JUMP_SPEED_Y				0.6f
#define SIMON_JUMP_DEFLECT_SPEED		0.2f
#define SIMON_GRAVITY					0.002f
#define SIMON_DIE_DEFLECT_SPEED			0.5f

#define SIMON_STATE_IDLE_2				600
#define SIMON_STATE_IDLE				500
#define SIMON_STATE_WALKING_RIGHT		100
#define SIMON_STATE_WALKING_LEFT		200
#define SIMON_STATE_JUMP				300
#define SIMON_STATE_DIE					400
#define SIMON_STATE_WALKING_CASTLE		900
#define SIMON_STATE_FIGHT				700
#define SIMON_STATE_SIT					800	
#define SIMON_STATE_STAIR_UP			1000
#define SIMON_STATE_STAIR_DOWN			1100
#define SIMON_STATE_HURT				1200


#define SIMON_ANI_IDLE_RIGHT			0
#define SIMON_ANI_WALKING_RIGHT			1
#define SIMON_ANI_IDLE_LEFT				2

#define SIMON_ANI_WALKING_LEFT			3
#define SIMON_ANI_IDLE_INTRO			4
#define SIMON_ANI_FIGHT_LEFT			5
#define SIMON_ANI_FIGHT_RIGHT			6

#define SIMON_ANI_SIT_JUMP_LEFT			7
#define SIMON_ANI_SIT_JUMP_RIGHT		8
#define SIMON_ANI_SIT_FIGHT_LEFT		9
#define SIMON_ANI_SIT_FIGHT_RIGHT		10

#define SIMON_ANI_UP_STAIR_LEFT			11
#define SIMON_ANI_UP_STAIR_RIGHT		12
#define SIMON_ANI_UP_STAIR_IDLE_RIGHT	13
#define SIMON_ANI_UP_STAIR_IDLE_LEFT	14
#define SIMON_ANI_DOWN_STAIR_LEFT		15
#define SIMON_ANI_DOWN_STAIR_RIGHT		16
#define SIMON_ANI_DOWN_STAIR_IDLE_RIGHT	17
#define SIMON_ANI_DOWN_STAIR_IDLE_LEFT	18
#define SIMON_ANI_HURT_RIGHT			19
#define SIMON_ANI_HURT_LEFT				20

#define SIMON_ANI_DIE					25


#define	SIMON_ALIVE						1


#define SIMON_UNTOUCHABLE_TIME			5000
#define SIMON_ATTACK_TIME				290
#define SIMON_THROW_TIME				450
class Simon : public CGameObject
{
	MorningStar *morningstar;
	float delaytime;
	int life;
	int status;
	int untouchable;
	DWORD untouchable_start;
	int hurtable;
	DWORD hurtable_start;
	DWORD attack_start;
	DWORD throw_start;
	int type;
	int numberofweapon;
	int energy;
	int hp;
	Dagger *dagger[3];
	Boomerang *boomerang[3];
	Axe *axe[3];
	HolyWater *holywater[3];
	StopWatch *stopwatch[3];
	bool IsDoor;
	bool IsControlKey;
public:
	Weapons *weapons[3];
	int anirender;
	bool IsGround;
	static bool IsFighting;
	static bool IsThrowing[3];
	bool IsJump;
	bool IsMove;
	bool IsSit;
	bool IsStair;
	bool IsHurt;
	bool IsStairUpLeft;
	bool IsStairUpRight;
	bool IsStairDownLeft;
	bool IsStairDownRight;
	int currentWeapon;
	D3DXVECTOR3 stairCollidePos;
	int ny;
	static bool isKillAll;
public:
	Simon();
	void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	void Render(Camera *camera);
	void Render();
	void SetState(int state);
	void OnStairHandle(int status);
	void AddEnergy(int energy);
	void SetLevel(int l) { status = l; }
	void resetAni(int aniID) { animations[aniID]->reset(); }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartHurting() {  IsHurt = true; hurtable = 1; hurtable_start = GetTickCount(); }
	void StartFighting() { vx = 0; IsFighting = true; attack_start = GetTickCount(); }
	void StartThrowing();
	void ResetAnimation();
	void UpgradeMorningstar();
	void IncreaseWeapon();
	int GetScore();
	int GetEnergy() { return this->energy; }
	void SetEnergy(int energy);
	int GetHP() { return this->hp; }
	void SetHP(int hp) { this->hp = hp; }
	int GetLife() { return life; }
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetTypeOfMorningstar(int type);
	int GetTypeOfMorningstar() { return this->type; }
	int GetNumberOfWeapon() { return numberofweapon; }
	void SetNumberOfWeapon(int number);
	void SetTypeOfWeapon(int type);
	int GetTypeOfWeapon() { return currentWeapon; }
	bool IsColliderWithDoor() { return IsDoor; }
	void SetColliderWithDoor(bool IsDoor) { this->IsDoor = IsDoor; }
	bool isControlKey() { return IsControlKey; }
	void SetControlKey(bool iscontrolkey) { this->IsControlKey = iscontrolkey; }
	static bool IsKillAll() { return isKillAll; }
	static void SetIsKillAll(bool IsKillAll) { isKillAll = IsKillAll; }
	~Simon();
};

