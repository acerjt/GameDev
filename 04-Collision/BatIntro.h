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
	virtual void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void SetState(int state);
	//virtual void Render(Camera *camera);
	BatIntro();
	~BatIntro();
};

