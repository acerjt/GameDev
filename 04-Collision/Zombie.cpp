#include "Zombie.h"
#include "Brick.h"
#include "Wall.h"
void Zombie::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = x;
	top = y;
	right = x+ BRICK_BBOX_WIDTH;
	bottom = y + ZOMBIE_BBOX_HEIGHT;
}

void Zombie::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	Enemy::Update(dt, coObjects);
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isEnable != false)
		CalcPotentialCollisions(coObjects, coEvents);
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (!(dynamic_cast<CBrick *>(e->obj)|| dynamic_cast<Wall *>(e->obj)))
			coEvents.erase(coEvents.begin() + i);
	}
	if (coEvents.size() == 0 && !IsStop)
	{
		x += dx;
		y += dy;
		isGrounded = false;
	}
	else if (!IsStop)
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				isGrounded = true;
				if (e->ny < 0)
				{
					x += dx;
					y += min_ty * dy + ny * 0.1f;
					if (ny != 0) vy = 0;
				}
				if (e->nx !=0)
				{
					x += dx;
					y += 1;
					if (ny != 0) vy = 0;
				}
			}

			if (dynamic_cast<Wall *>(e->obj))
			{
				if (e->nx != 0) {
					if (this->nx>0)
					SetState(ZOMBIE_STATE_WALKING_LEFT);
					else
						SetState(ZOMBIE_STATE_WALKING_RIGHT);
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
	if (!isGrounded)
		vy += 0.002 * dt;
}
void Zombie::Render(Camera *camera)
{
	
	if (isEnable == true)
	{	
		if (state == ZOMBIE_STATE_WALKING_LEFT)
			ani = ZOMBIE_ANI_WALKING_LEFT;
		else if (state == ZOMBIE_STATE_WALKING_RIGHT)
			ani = ZOMBIE_ANI_WALKING_RIGHT;
		animations[ani]->Render(camera, x, y);
	}
	Enemy::Render(camera);
}


void Zombie::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ZOMBIE_STATE_WALKING_LEFT:
		vx = -ZOMBIE_WALKING_SPEED;
		nx = -1;
		break;
	case ZOMBIE_STATE_WALKING_RIGHT:
		vx = ZOMBIE_WALKING_SPEED;
		nx = 1;
		break;
	case ZOMBIE_STATE_IDLE:
		vx = 0;
		break;
	}
}


Zombie::Zombie():Enemy(1)
{
	this->AddAnimation(18001);
	this->AddAnimation(18002);
	damage = 2;
	point = 100;
}


Zombie::~Zombie()
{
}
