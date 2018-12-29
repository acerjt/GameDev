#include "FishMan.h"
#include "Brick.h"


void FishMan::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + FISH_MAN_BBOX_WIDTH;
	bottom=y + FISH_MAN_BBOX_HEIGHT;
}

void FishMan::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);
		vy += 0.002 * dt;
	if (isEnable == true && !isDead && IsStop!=true)
	{
		timeDelay += dt;
		if (!fireball->IsEnable() && state != FISH_MAN_STATE_JUMP && isGrounded&& timeDelay>2000)
		{
			SetState(FISH_MAN_STATE_FIRE);
			timeDelay = 0;
			if(nx>0)
				fireball->nx=1;
			else
				fireball->nx = -1;
			fireball->SetPosition(this->GetPosition().x, this->GetPosition().y + 10);
			fireball->isEnable = true;
			fireball->SetDamage(this->damage);		
		}
		if (state == FISH_MAN_STATE_FIRE && timeDelay > 1000)
		{
		
			if (nx > 0)
				nx = -1;
			else
				nx = 1;
			if(nx>0)
				SetState(FISH_MAN_STATE_WALKING_RIGHT);
			else
				SetState(FISH_MAN_STATE_WALKING_LEFT);
			timeDelay = 0;
		}
		if (state == FISH_MAN_STATE_JUMP && isGrounded)
		{
			if (nx > 0)
				SetState(FISH_MAN_STATE_WALKING_RIGHT);
			else
				SetState(FISH_MAN_STATE_WALKING_LEFT);
		}
		
	}
	fireball->Update(dt);
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	if (isEnable != false)
		CalcPotentialCollisions(coObjects, coEvents);
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (!(dynamic_cast<CBrick *>(e->obj)))
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
			vy = 0;
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{

				if (e->ny < 0)
				{
					isGrounded = true;
					x += dx;

				}
			
				if (e->nx != 0)
					x += dx;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
}

void FishMan::Render(Camera * camera)
{
	if (isEnable == true)
	{

		if (state == FISH_MAN_STATE_WALKING_LEFT)
			anirender = FISH_MAN_ANI_WALKING_LEFT;
		else if (state == FISH_MAN_STATE_WALKING_RIGHT)
			anirender = FISH_MAN_ANI_WALKING_RIGHT;
		else if (state == FISH_MAN_STATE_JUMP)
		{
			if (nx > 0)
				anirender = FISH_MAN_ANI_JUMP_RIGHT;
			else
				anirender = FISH_MAN_ANI_JUMP_LEFT;
		}
		else if (state == FISH_MAN_STATE_FIRE)
		{
			if (nx > 0)
				anirender = FISH_MAN_ANI_FIRE_RIGHT;
			else
				anirender = FISH_MAN_ANI_FIRE_LEFT;
		
		}

		animations[anirender]->Render(camera, x, y);
		
	}
	fireball->Render(camera);
	Enemy::Render(camera);
}

void FishMan::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case FISH_MAN_STATE_WALKING_LEFT:
		vx = -FISH_MAN_WALKING_SPEED;
		break;
	case FISH_MAN_STATE_WALKING_RIGHT:
		vx = FISH_MAN_WALKING_SPEED;
		break;
	case FISH_MAN_STATE_JUMP:
		vy = -FISH_MAN_JUMP_SPEED;
		vx = 0;
		break;
	case FISH_MAN_STATE_FIRE:
		vx = 0;
		break;
	}
}

FishMan::FishMan():Enemy(1)
{
	this->AddAnimation(23001);
	this->AddAnimation(23002);
	this->AddAnimation(23003);
	this->AddAnimation(23004);
	this->AddAnimation(23005);
	this->AddAnimation(23006);
	srand(time(0));
	damage = rand()%4;
	if (damage < 2)
		damage = 2;
	point = 300;
	fireball = new FireBall();
	fireball->SetEnable(false);
}


FishMan::~FishMan()
{
}
