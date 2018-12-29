#pragma once
#include "Enemy.h"

#define ZOMBIE_WALKING_SPEED 0.06f

#define ZOMBIE_BBOX_WIDTH 34
#define ZOMBIE_BBOX_HEIGHT 64

#define ZOMBIE_STATE_WALKING_LEFT	100
#define ZOMBIE_STATE_WALKING_RIGHT	200					
#define ZOMBIE_STATE_DIE			300
#define ZOMBIE_STATE_IDLE			400

#define ZOMBIE_ANI_WALKING_LEFT		0
#define ZOMBIE_ANI_WALKING_RIGHT	1
#define ZOMBIE_ANI_DIE 10

class Zombie: public Enemy
{
	int ani;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void SetState(int state);
	Zombie();
	~Zombie();
};

