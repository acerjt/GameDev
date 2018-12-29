#include "VampireBat.h"

void VampireBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + VAMPIRE_BAT_BBOX_WIDTH;
	bottom = y + VAMPIRE_BAT_BBOX_HEIGHT;
}

void VampireBat::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
	if (nx==1)
	{
		SetState(VAMPIRE_BAT_STATE_WALKING_RIGHT);
		x += vx * dt;
		y = std::sin(x * 0.03) * 3 + y;
	}
	else if (nx==-1)
	{
		SetState(VAMPIRE_BAT_STATE_WALKING_LEFT);
		x += vx * dt;
		y = std::sin(x * 0.03) * 3 + y;
	}
}

void VampireBat::Render(Camera * camera)
{
	if (isEnable == true)
	{
		animations[anirender]->Render(camera, x, y);
	}
	Enemy::Render(camera);
}

void VampireBat::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case VAMPIRE_BAT_STATE_WALKING_LEFT:
		vx = -VAMPIRE_BAT_WALKING_SPEED;
		anirender = 0;
		break;
	case VAMPIRE_BAT_STATE_WALKING_RIGHT:
		vx = VAMPIRE_BAT_WALKING_SPEED;
		anirender = 1;
		break;
	}

}
VampireBat::VampireBat():Enemy(1)
{
	this->AddAnimation(22001);
	this->AddAnimation(22002);
	damage = 2;
	point = 200;
	nx = -1;
}


VampireBat::~VampireBat()
{
}
