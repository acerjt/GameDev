#pragma once
#include "Enemy.h"
#include <time.h>
#include "FireBall.h"


#define FISH_MAN_BBOX_WIDTH 32
#define FISH_MAN_BBOX_HEIGHT 64

#define FISH_MAN_WALKING_SPEED  0.1
#define FISH_MAN_JUMP_SPEED		0.6

#define FISH_MAN_STATE_JUMP				100
#define FISH_MAN_STATE_WALKING_LEFT		200
#define FISH_MAN_STATE_WALKING_RIGHT	300
#define FISH_MAN_STATE_FIRE				400


#define FISH_MAN_ANI_JUMP_LEFT		0
#define FISH_MAN_ANI_WALKING_LEFT	1
#define FISH_MAN_ANI_FIRE_LEFT		2
#define FISH_MAN_ANI_JUMP_RIGHT		3
#define FISH_MAN_ANI_WALKING_RIGHT	4
#define FISH_MAN_ANI_FIRE_RIGHT		5

class FishMan:public Enemy
{
	int anirender;
	DWORD timeDelay;
	FireBall *fireball;
	bool IsFiring;
	DWORD firing_start;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void SetState(int state);
	FireBall* GetFireBall() { return fireball; }
	FishMan();
	~FishMan();
};

