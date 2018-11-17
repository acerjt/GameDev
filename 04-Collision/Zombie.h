#pragma once
#include "GameObject.h"

#define ZOMBIE_WALKING_SPEED 0.05f

#define ZOMBIE_BBOX_WIDTH 34
#define ZOMBIE_BBOX_HEIGHT 64
#define ZOMBIE_BBOX_HEIGHT_DIE 9

#define ZOMBIE_STATE_WALKING 100
#define ZOMBIE_STATE_DIE 200
#define ZOMBIE_STATE_IDLE 300

#define ZOMBIE_ANI_WALKING 0
#define ZOMBIE_ANI_DIE 1

class Zombie: public CGameObject
{
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render(Camera *camera);
	virtual void Render();
public:
	virtual void SetState(int state);
	Zombie();
	~Zombie();
};

