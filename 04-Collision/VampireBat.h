#pragma once
#include "Enemy.h"

#define VAMPIRE_BAT_BBOX_HEIGHT 31
#define VAMPIRE_BAT_BBOX_WIDTH 31

#define VAMPIRE_BAT_WALKING_SPEED 0.1
#define VAMPIRE_BAT_STATE_WALKING_LEFT  100
#define VAMPIRE_BAT_STATE_WALKING_RIGHT 200

class VampireBat:public Enemy
{
	int anirender;
public:
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Render(Camera *camera);
	void SetState(int state);
	VampireBat();
	~VampireBat();
};

