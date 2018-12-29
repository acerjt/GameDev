#include "BatIntro.h"

void BatIntro::Render(Camera *camera)
{
	animations[0]->Render(camera,x, y);
}

void BatIntro::Update(DWORD dt)
{
	CGameObject::Update(dt);
	x += dx;
	y -= dy;
}

void BatIntro::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BAT_INTRO_STATE_FLY_UP:
		vx = BAT_INTRO_SPEED;
		vy = BAT_INTRO_SPEED;
		break;
	case BAT_INTRO_STATE_FLY_STRAIGHT:
		vx = -BAT_INTRO_SPEED ;
		vy = BAT_INTRO_SPEED *0.2;
		break;
	}

}

void BatIntro::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = t = r = b = 0;
}

BatIntro::BatIntro()
{
	this->AddAnimation(4001);
}


BatIntro::~BatIntro()
{
}
