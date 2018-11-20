#pragma once
#include "GameObject.h"
#include "MorningStar.h"


#define SIMON_WALKING_SPEED		0.11f 
#define SIMON_JUMP_SPEED_Y		0.6f
#define SIMON_JUMP_DEFLECT_SPEED 0.2f
#define SIMON_GRAVITY			0.002f
#define SIMON_DIE_DEFLECT_SPEED	 0.5f

#define SIMON_STATE_IDLE_2			600
#define SIMON_STATE_IDLE			500
#define SIMON_STATE_WALKING_RIGHT	100
#define SIMON_STATE_WALKING_LEFT	200
#define SIMON_STATE_JUMP			300
#define SIMON_STATE_DIE				400
//#define SIMON_STATE_FIGHT_RIGHT		500
#define SIMON_STATE_FIGHT			700
#define SIMON_STATE_SIT				800	

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

#define SIMON_ANI_DIE					11


#define	SIMON_ALIVE		1


#define SIMON_UNTOUCHABLE_TIME 5000
#define SIMON_ATTACK_TIME 400
class Simon : public CGameObject
{
	MorningStar *morningstar;
	float delaytime;
	int life;
	int status;
	int untouchable;
	DWORD untouchable_start;
	DWORD attack_start;
	DWORD jump_start;
	int type;
	//int anirender;
	int noSubWeapon;
public:
	bool IsFighting;
	bool IsJump = false;
	bool IsMove;
	bool IsSit;
	//bool IsSitting = true;
	Simon();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render(Camera *camera);
	virtual void Render();
	void SetState(int state);
	void SetLevel(int l) { status = l; }
	void resetAni(int aniID) { animations[aniID]->reset(); }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartFighting() { IsFighting = true; attack_start = GetTickCount(); }
	void StartJump() { IsJump = true; jump_start = GetTickCount();  }
	void MorningStarCheckCollider(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetTypeOfMorningstar(int type);
	int GetTypeOfMorningstar() { return this->type; }
	int GetNoSubWeapon() { return noSubWeapon; }
	~Simon();
};

