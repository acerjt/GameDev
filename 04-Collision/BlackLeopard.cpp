#include "BlackLeopard.h"
#include "Brick.h"


void BlackLeopard::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + BLACK_LEOPARD_BBOX_WIDTH;
	bottom = y + BLACK_LEOPARD_BBOX_HEIGHT;
}

void BlackLeopard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	Enemy::Update(dt, coObjects);

	if (state == BLACK_LEOPARD_STATE_IDLE)
		isGroundedNext = true;
	if (!isGroundedNext)
	{
		SetState(BLACK_LEOPARD_STATE_JUMP);
		isGroundedNext = true;
	}
	bool state1 = isGrounded;
	if (state1&&state!=BLACK_LEOPARD_STATE_IDLE)
		isGroundedNext = false;
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
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<CBrick *>(e->obj))
			{
				CBrick *brick = dynamic_cast<CBrick *>(e->obj);
					if (e->ny < 0)
					{
						x += dx;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
						y += min_ty * dy + ny * 0.1f;
						if (ny != 0) vy = 0;
						isGrounded = true;
						isGroundedNext = true;
						IsJump = false;
					}
					if (brick->GetType() == -2)
					{
						
						if ( state ==BLACK_LEOPARD_STATE_JUMP && this->nx == -1)
							SetState(BLACK_LEOPARD_STATE_WALKING_RIGHT);
						else if (state == BLACK_LEOPARD_STATE_JUMP && this->nx == 1)
							SetState(BLACK_LEOPARD_STATE_WALKING_LEFT);
					}
			}
			
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}
	
	if (!isGrounded)
		vy += 0.003 * dt;
}

void BlackLeopard::Render(Camera * camera)
{
	if (isEnable == true)
	{

		if (state == BLACK_LEOPARD_STATE_WALKING_LEFT)
			ani = BLACK_LEOPARD_ANI_WALKING_LEFT;
		else if (state == BLACK_LEOPARD_STATE_WALKING_RIGHT)
			ani = BLACK_LEOPARD_ANI_WALKING_RIGHT;
		 if (nx > 0)
		{
			if (state == BLACK_LEOPARD_STATE_IDLE)
				ani = BLACK_LEOPARD_ANI_IDLE_RIGHT;
			if (IsJump)
				ani = BLACK_LEOPARD_ANI_JUMP_RIGHT;
			if (!IsJump&&vx > 0)
				ani = BLACK_LEOPARD_ANI_WALKING_RIGHT;
		}
		 if (nx<0)
		{
			if (state == BLACK_LEOPARD_STATE_IDLE)
				ani = BLACK_LEOPARD_ANI_IDLE_LEFT;
			if (IsJump)
				ani = BLACK_LEOPARD_ANI_JUMP_LEFT;
			if (!IsJump&&vx <0)
				ani = BLACK_LEOPARD_ANI_WALKING_LEFT;
		}

		animations[ani]->Render(camera, x, y);
	}
	Enemy::Render(camera);
	//RenderBoundingBox(camera);
}


void BlackLeopard::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case BLACK_LEOPARD_STATE_WALKING_LEFT:
		vx = -BLACK_LEOPARD_WALKING_SPEED;
		vy = 0;
		break;
	case BLACK_LEOPARD_STATE_WALKING_RIGHT:
		vx = BLACK_LEOPARD_WALKING_SPEED;
		vy = 0;
		break;
	case BLACK_LEOPARD_STATE_IDLE:
		vx = 0;
		vy = 0;
		break;
	case BLACK_LEOPARD_STATE_JUMP:
			vy = -BLACK_LEOPARD_JUMP_SPEED;
			IsJump = true;
			break;
	}
}

BlackLeopard::BlackLeopard():Enemy(1)
{
	this->AddAnimation(19001);
	this->AddAnimation(19002);
	this->AddAnimation(19003);
	this->AddAnimation(19004);
	this->AddAnimation(19005);
	this->AddAnimation(19006);
	damage = 2;
	point = 200;
	isGroundedNext = true;
	isGrounded = false;
	nx = -1;
}


BlackLeopard::~BlackLeopard()
{
}
