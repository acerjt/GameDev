#pragma once
#include "GameObject.h"

#define BAT_INTRO_SPEED 0.05f
#define	BAT_INTRO_BBOX_WIDTH 15
#define BAT_INTRO_BBOX_HEIGHT 15
#define BAT_INTRO_STATE_FLY_UP 100
#define BAT_INTRO_STATE_FLY_STRAIGHT 200
class BatIntro: public CGameObject
{
public:
	void Update(DWORD dt);
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetState(int state);
	BatIntro();
	~BatIntro();
};

