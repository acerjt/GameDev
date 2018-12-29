#pragma once
#include "Enemy.h"
#include <time.h>
#include "Simon.h"

#define PHANTOM_BAT_STATE_IDLE		100
#define PHANTOM_BAT_STATE_MOVE		200
#define PHANTOM_BAT_STATE_HURT		300

#define HURT_TIME	10
#define WAIT_TIME	750
#define CHASE_TIME	50

class PhantomBat:public Enemy
{
	CAnimation * ani;
	D3DXVECTOR2 random;
	D3DXVECTOR2 simonPos;
	D3DXVECTOR2 batPos;
	float ny;
	float nx;
	float distance;
	bool isFlytorandompos;
	bool isFlytosimonpos;
	float waitTime;
	float hurtTime;
	DWORD delayTime;
	int previousHP; 
	float introTime;
	DWORD chaseTime;
	int anirender;
	bool isHurted;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt);
	void Render(Camera *camera);
	void Render();
	void SetState(int state);
	void CalculateSimonPos(Simon *simon, DWORD dt);
	void Fly(DWORD dt);
	void RandomPos();
	bool Intro(DWORD dt);
	void CheckHPChange();
	void CheckHurtTime(DWORD dt);
	void FlyToRandomPos(DWORD dt);
	PhantomBat();
	~PhantomBat();
};

