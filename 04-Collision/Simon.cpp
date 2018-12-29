#include <algorithm>
#include "debug.h"
#include "Item.h"
#include "Brick.h"
#include "Simon.h"
#include "Game.h"
#include "Zombie.h"
#include "Torch.h"
#include "Candle.h"
#include "MapCollision.h"
#include "TransparentObject.h"
#include "StairCheckObject.h"
#include "Enemy.h"
#include "Wall.h"
#include "Door.h"
#include "VampireBat.h"
#include "FireBall.h"
bool Simon::IsFighting = false;
bool Simon::IsThrowing[3] = { false,false,false };
bool Simon::isKillAll = false;

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	CGameObject::Update(dt);
	if (IsStair == true)
	{
		vy = 0;
	}
	if ((IsStair != true && IsGround == false) ||IsHurt)
		vy += SIMON_GRAVITY * dt;
	if (dy == 0)
	{
		IsJump = false;
		IsGround = true;	
	}
	if (IsFighting)
	{
		morningstar->SetPosition(this->x, this->y, IsSit);
		if (morningstar->GetCurrentFrameOfMorningStar() == 2)
		{
			morningstar->Update(dt, coObjects);
		}
		if (!IsFighting)
			ResetAnimation();
		if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
		{
			ResetAnimation();
			morningstar->ResetAnimation();
			attack_start = 0;
			IsFighting = false;
		}
	}
	for (int i = 0; i < numberofweapon; i++)
	{
		if (IsThrowing[i])
		{
			if (animations[anirender]->getCurrentFrame() == 2)
			{

				if (!weapons[i]->IsEnable())
				{
					weapons[i]->SetPosition(this->x, this->y);
					weapons[i]->SetEnable(true);

					if (this->nx == -1)
						weapons[i]->nx = -1;
					else
						weapons[i]->nx = 1;
				}


			}
			if (GetTickCount() - throw_start > SIMON_THROW_TIME)
			{
				throw_start = 0;
				IsThrowing[i] = false;
				this->resetAni(SIMON_ANI_FIGHT_LEFT);
				this->resetAni(SIMON_ANI_FIGHT_RIGHT);
			}
		}
	}

	for (int i = 0; i < numberofweapon; i++)
	{
		if (!weapons[i])
			weapons[i] = weapons[0];
		if (weapons[i]->IsEnable())
			weapons[i]->Update(i,dt, coObjects);
		
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	//reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > 2000)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	
	if (this->GetState() != SIMON_STATE_SIT)
		IsSit = false;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy *>(coObjects->at(i)))
		{
			Enemy *enemy = dynamic_cast<Enemy *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (untouchable == 0)
					{
						if (enemy->isEnable != false)
						{
							if (hp > 0)
							{
								hp -= enemy->GetDamage();		
								StartUntouchable();
								SetState(SIMON_STATE_HURT);
								StartHurting();
								if (dynamic_cast<VampireBat *>(coObjects->at(i)))
								{
									enemy->SetEnable(false);
									enemy->GetColliderEffect()->SetEnable(true);
								}
							}
							else
								SetState(SIMON_STATE_DIE);
						}
					}
					
					
				}
			}
		}
		if (dynamic_cast<StairCheckObject *>(coObjects->at(i)))
		{
			StairCheckObject *staircheckobject = dynamic_cast<StairCheckObject *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			staircheckobject->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if (staircheckobject->GetType() == OBJECT_STAIR_UP_RIGHT)
				{
					if (state == SIMON_STATE_STAIR_UP)
						IsStair = false;
					IsStairUpRight = true;
					IsStairUpLeft = false;
					IsStairDownRight = false;
					IsStairDownLeft = false;
					stairCollidePos = staircheckobject->GetPosition();
				}
				else
					if (staircheckobject->GetType() == OBJECT_STAIR_UP_LEFT)
					{
						if (state == SIMON_STATE_STAIR_UP)
							IsStair = false;
						IsStairUpRight = false;
						IsStairUpLeft = true;
						IsStairDownRight = false;
						IsStairDownLeft = false;
						stairCollidePos = staircheckobject->GetPosition();
					}
					else
						if (staircheckobject->GetType() == OBJECT_STAIR_DOWN_LEFT)
						{
							if (state == SIMON_STATE_STAIR_DOWN)
								IsStair = false;
							IsGround = false;
							IsStairUpRight = false;
							IsStairUpLeft = false;
							IsStairDownRight = false;
							IsStairDownLeft = true;
							stairCollidePos = staircheckobject->GetPosition();
						}
						else
							if (staircheckobject->GetType() == OBJECT_STAIR_DOWN_RIGHT)
							{
								if (state == SIMON_STATE_STAIR_DOWN)
									IsStair = false;
								IsStairUpRight = false;
								IsStairUpLeft = false;
								IsStairDownRight = true;
								IsStairDownLeft = false;
								stairCollidePos = staircheckobject->GetPosition();
							}
			}
		}
	}
	if (IsHurt) {
		if (GetTickCount() - hurtable_start > 600)
		{
			hurtable_start = 0;
			hurtable = 0;
			IsHurt = false;

		}
	}
	//No collision occured, proceed normally
	if (IsStair)
		for (UINT i = 0; i < coEvents.size(); i++)
		{
			LPCOLLISIONEVENT e = coEvents[i];
			if (dynamic_cast<CBrick *>(e->obj))
			{
				coEvents.erase(coEvents.begin() + i);
			}
		}
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT e = coEvents[i];
		if (dynamic_cast<Torch *>(e->obj) || dynamic_cast<Candle *>(e->obj))
		{
			coEvents.erase(coEvents.begin() + i);
		}
	}
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
		IsGround = false;

	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Item *>(e->obj))
			{
				Item *item = dynamic_cast<Item *>(e->obj);
				if (item->isEnable == true) {
					switch (item->GetItemType())
					{
					case ITEM_SMALL_HEART:
						AddEnergy(1);
						break;
					case ITEM_BIG_HEART:
						AddEnergy(5);
						break;
					case ITEM_ROAST:
						if (hp + 6 < 16)
							hp += 6;
						else
							SetHP(16);
						break;
					case ITEM_MORNINGSTAR:
						UpgradeMorningstar();
						break;
					case ITEM_BALL:

						break;
					case ITEM_MONEY_RED:
						Enemy::SetScore(1000);
						break;
					case ITEM_MONEY_WHITE:
						Enemy::SetScore(700);
						break;
					case ITEM_MONEY_PURPLE:
						Enemy::SetScore(400);
						break;
					case ITEM_MONEY:
						if (item->GetCurrentFrame() == 0)
							Enemy::SetScore(1000);
						else if (item->GetCurrentFrame() == 1)
							Enemy::SetScore(700);
						else
							Enemy::SetScore(400);
						break;
					case ITEM_INVISIBLE:
						StartUntouchable();
						break;
					case ITEM_CROSS:
						SetIsKillAll(true);
						break;
					case ITEM_UPGRADE_1:
						IncreaseWeapon();
						break;
					case ITEM_UPGRADE_2:
						IncreaseWeapon();
						break;
					default:
						SetTypeOfWeapon(item->GetItemType());
						break;
					}

					item->isEnable = false;
					item->isDead = true;
				}


			}
			if (dynamic_cast<TransparentObject *>(e->obj))
			{
				TransparentObject *transparentobject = dynamic_cast<TransparentObject *>(e->obj);
				if (transparentobject->isEnable == true)
				{
					transparentobject->isEnable = false;
					transparentobject->isDead = true;

				}
			}
			if (dynamic_cast<FireBall *>(e->obj))
			{
				FireBall *fireball = dynamic_cast<FireBall *>(e->obj);
				if (untouchable == 0)
				{
					if (fireball->isEnable == true)
					{
						this->hp -= fireball->GetDamage();
						StartUntouchable();
						SetState(SIMON_STATE_HURT);
						StartHurting();
						fireball->isEnable = false;

					}
				}
			}
			if (dynamic_cast<Door *>(e->obj))
			{
				Door *door = dynamic_cast<Door *>(e->obj);
				if(door->GetType()== 21)
				if (e->nx == -1)
				{
					IsDoor = true;
					IsControlKey = false;
					SetState(SIMON_STATE_IDLE);
				}
			}
			if (dynamic_cast<CBrick *>(e->obj) || dynamic_cast<MapCollision *>(e->obj) || dynamic_cast<Wall *>(e->obj))
			{
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.1f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.1f;
					if (!IsHurt) {
						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
					}
				}
				IsStair = false;
				IsStairUpRight = false;
				IsStairUpLeft = false;
				IsStairDownRight = false;
				IsStairDownLeft = false;
			}
			else
			{
				x += dx;
				if (ny < 0)
					y += dy + ny * 0.7f;
				else if (ny > 0)
					y += dy + ny * -0.7f;
			}

		}
	}
	//clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++)
	{
		delete coEvents[i];
	}

}


void Simon::Render(Camera *camera)
{
	if (state == SIMON_STATE_DIE)
		anirender = SIMON_ANI_DIE;
	else
		if (life > 0)
		{
			if (vx == 0)
			{	
				if ((nx > 0) && (state == SIMON_STATE_SIT) && IsFighting)
				{
					anirender = SIMON_ANI_SIT_FIGHT_RIGHT;
					if (type == MORNINGSTAR)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT);
					}
					if (type == MORNINGSTAR_1)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_1);
					}
					if (type == MORNINGSTAR_2)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_2);
					}
				}
				else if ((nx > 0) && (state == SIMON_STATE_SIT))
				{
					anirender = SIMON_ANI_SIT_JUMP_RIGHT;
				}
				else if ((nx > 0) && IsFighting)
				{
					anirender = SIMON_ANI_FIGHT_RIGHT;
					if (type == MORNINGSTAR)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT);
					}
					if (type == MORNINGSTAR_1)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_1);
					}
					if (type == MORNINGSTAR_2)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_2);
					}

				}
				else if ((nx < 0) && (state == SIMON_STATE_SIT) && IsFighting)
				{
					anirender = SIMON_ANI_SIT_FIGHT_LEFT;
					if (type == MORNINGSTAR)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT);
					}
					if (type == MORNINGSTAR_1)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_1);
					}
					if (type == MORNINGSTAR_2)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_2);
					}
				}
				else if ((nx < 0) && (state == SIMON_STATE_SIT))
				{
					anirender = SIMON_ANI_SIT_JUMP_LEFT;
				}
				else if ((nx < 0) && IsFighting)
				{
					anirender = SIMON_ANI_FIGHT_LEFT;
					if (type == MORNINGSTAR)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT);
					}
					if (type == MORNINGSTAR_1)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_1);
					}
					if (type == MORNINGSTAR_2)
					{
						morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_2);
					}

				}
				else if (nx < 0)
				{
					anirender = SIMON_ANI_IDLE_LEFT;
					for (int i = 0; i < 3; i++)
					{
						if (IsThrowing[i])
						{
							anirender = SIMON_ANI_FIGHT_LEFT;

						}
					}
				}
				else if (nx > 0)
				{ 
					anirender = SIMON_ANI_IDLE_RIGHT;
				
					for (int i = 0; i < 3; i++)
					{
						if (IsThrowing[i])
						{
							anirender = SIMON_ANI_FIGHT_RIGHT;

						}

					}
				}
			}
			else if (vx > 0)
			{
				if (nx < 0 && IsHurt)
					anirender = SIMON_ANI_HURT_LEFT;
				else
				 anirender = SIMON_ANI_WALKING_RIGHT;
			}
			else
			{
			if (nx > 0 && IsHurt)
				anirender = SIMON_ANI_HURT_RIGHT;
				else anirender = SIMON_ANI_WALKING_LEFT;
			}
		}

	for (int i = 0; i < numberofweapon; i++)
		if (weapons[i]->IsEnable())
			weapons[i]->Render(camera);
	if (state == SIMON_STATE_IDLE_2)
		anirender = SIMON_ANI_IDLE_INTRO;
	if (IsJump == true && IsFighting == true && state == SIMON_STATE_WALKING_RIGHT)
	{
		anirender = SIMON_ANI_FIGHT_RIGHT;
		anirender = SIMON_ANI_FIGHT_RIGHT;
		if (type == MORNINGSTAR)
		{
			morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT);
		}
		if (type == MORNINGSTAR_1)
		{
			morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_1);
		}
		if (type == MORNINGSTAR_2)
		{
			morningstar->Render(camera, MORNINGSSTAR_ANI_RIGHT_2);
		}
	}

	else
		if (IsJump == true && IsFighting == true && state == SIMON_STATE_WALKING_LEFT)
		{
			anirender = SIMON_ANI_FIGHT_LEFT;
			if (type == MORNINGSTAR)
			{
				morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT);
			}
			if (type == MORNINGSTAR_1)
			{
				morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_1);
			}
			if (type == MORNINGSTAR_2)
			{
				morningstar->Render(camera, MORNINGSSTAR_ANI_LEFT_2);
			}

		}
	if (IsJump == true &&!IsHurt&& anirender != SIMON_ANI_FIGHT_LEFT && anirender != SIMON_ANI_FIGHT_RIGHT)
		if (nx < 0)
			anirender = SIMON_ANI_SIT_JUMP_LEFT;
		else if (nx > 0)
			anirender = SIMON_ANI_SIT_JUMP_RIGHT;

	if (IsStairDownLeft&&vy == 0 && vx == 0 && nx < 0)
		anirender = SIMON_ANI_UP_STAIR_IDLE_LEFT;
	if (IsStairDownLeft&&vy == 0 && vx == 0 && nx > 0)
		anirender = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;
	else if (IsStairDownLeft && vx > 0 && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_DOWN_STAIR_RIGHT;
		nx = 1;
	}
	else if (IsStairDownLeft && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_UP_STAIR_LEFT;
		nx = -1;
	}
	else if (IsStairDownRight &&vy == 0 && vx == 0 && nx > 0)
		anirender = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
	else if (IsStairDownRight &&vy == 0 && vx == 0 && nx < 0)
		anirender = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;

	else if (IsStairDownRight && vx < 0 && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_DOWN_STAIR_LEFT;
	}
	else if (IsStairDownRight && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_UP_STAIR_RIGHT;
	}
	if (IsStairUpLeft && vy == 0 && vx == 0 && nx < 0)
		anirender = SIMON_ANI_DOWN_STAIR_IDLE_LEFT;
	else if (IsStairUpLeft && vy == 0 && vx == 0 && nx > 0)
		anirender = SIMON_ANI_UP_STAIR_IDLE_RIGHT;
	else if (IsStairUpLeft && vx > 0 && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_UP_STAIR_RIGHT;
		nx = 1;
	}
	else if (IsStairUpLeft && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_DOWN_STAIR_LEFT;
		nx = -1;
	}
	else if (IsStairUpRight &&vy == 0 && vx == 0 && nx > 0)
		anirender = SIMON_ANI_DOWN_STAIR_IDLE_RIGHT;
	else if (IsStairUpRight &&vy == 0 && vx == 0 && nx < 0)
		anirender = SIMON_ANI_UP_STAIR_IDLE_LEFT;

	else if (IsStairUpRight && vx < 0 && state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_UP_STAIR_LEFT;
		nx = -1;
	}
	else if (IsStairUpRight&& state != SIMON_STATE_WALKING_LEFT && state != SIMON_STATE_WALKING_RIGHT && state != SIMON_STATE_IDLE)
	{
		anirender = SIMON_ANI_DOWN_STAIR_RIGHT;
		nx = 1;
	}


	int alpha = 255;
	if (untouchable) alpha = 128;
	animations[anirender]->Render(camera, x, y, alpha);


}
void Simon::Render()
{

}

void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		if (IsFighting == true && IsJump == false)
		{
			anirender = SIMON_ANI_FIGHT_RIGHT;
		}
		else if (IsStair == true)
			vx = 0;
		else
		{
			vx = SIMON_WALKING_SPEED;
			nx = 1;
		}
		break;
	case SIMON_STATE_WALKING_LEFT:
		if (IsFighting == true && IsJump == false)
		{
			anirender = SIMON_ANI_FIGHT_LEFT;
		}
		else if (IsStair == true)
			vx = 0;
		else
		{
			vx = -SIMON_WALKING_SPEED;
			nx = -1;
		}
		break;
	case SIMON_STATE_JUMP:
		IsJump = true;
		IsGround = false;
		if (IsStair)
			vy = 0;
		else
			vy = -SIMON_JUMP_SPEED_Y;
		break;
	case SIMON_STATE_IDLE:
			vx = 0;
		break;
	case SIMON_STATE_DIE:
		vy = -SIMON_DIE_DEFLECT_SPEED;
		break;
	case SIMON_STATE_IDLE_2:
		vx = 0;
		break;
	case SIMON_STATE_FIGHT:
		IsFighting = true;
		vx = 0;
		break;
	case SIMON_STATE_SIT:
		vx = 0;
		IsSit = true;
		break;
	case SIMON_STATE_WALKING_CASTLE:
		vx = SIMON_WALKING_CASTLE_SPEED;
		IsControlKey = false;
		break;
	case SIMON_STATE_STAIR_UP:
		if (IsStairDownRight)
		{
			vx = 0.1;
			vy = -0.1;
		}
		else if (IsStairDownLeft)
		{

			vx = -0.1;
			vy = -0.1;
		}
		if (IsStairUpLeft)
		{
			vx = 0.1;
			vy = -0.1;
		}
		else if (IsStairUpRight)
		{
			vx = -0.1;
			vy = -0.1;
		}

		break;
	case SIMON_STATE_STAIR_DOWN:
		if (IsStairUpRight)
		{
			vx = 0.1;
			vy = 0.1;
		}
		else if (IsStairUpLeft)
		{
			vx = -0.1;
			vy = 0.1;
		}
		if (IsStairDownRight)
		{
			vx = -0.1;
			vy = 0.1;
		}
		else if (IsStairDownLeft)
		{
			vx = 0.1;
			vy = 0.1;
		}

		break;
	case SIMON_STATE_HURT:
		IsGround = false;
		if (IsStair == true){
			vy = 0;
			vx = 0;
		}
		else
		{
			if (nx > 0)
			{
				vx = -0.1;
			}
			if (nx < 0)
			{
				vx = 0.1;
			}
			if(dy<=0||vy>=0||dy>0)
			vy = -0.4;

		}
		break;
	}
}

void Simon::OnStairHandle(int status)
{
	if (IsStairDownRight)
	{
		if (status == 1)
		{
			if (this->GetPosition().x + 46 > stairCollidePos.x + 20 && !IsStair)
			{
				SetState(SIMON_STATE_WALKING_LEFT);
				nx = -1;
			}
			else {
				IsStair = true;
				nx = 1;
				ny = 1;
			}
		}
	}
	else if (IsStairDownLeft)
	{
		if (status == 1)
		{
			if (this->GetPosition().x < stairCollidePos.x && !IsStair)
			{
				SetState(SIMON_STATE_WALKING_RIGHT);
				nx = 1;
			}
			else {
				IsStair = true;
				nx = -1;
				ny = 1;
			}
		}
	}

	if (IsStairUpRight)
	{

		if (status == 2)
		{
			if (this->GetPosition().x < stairCollidePos.x && !IsStair)
			{
				SetState(SIMON_STATE_WALKING_RIGHT);
				nx = 1;
			}
			else
			{
				IsStair = true;
				nx = 1;
				ny = -1;
			}
		}
	}
	else if (IsStairUpLeft)
	{
		if (status == 2)
		{
			if (this->GetPosition().x + 46 > stairCollidePos.x + 20 && !IsStair)
			{
				SetState(SIMON_STATE_WALKING_LEFT);
				nx = -1;
			}
			else
			{
				IsStair = true;
				nx = -1;
				ny = -1;
			}
		}
	}

	if (IsStair)
	{
		if (nx * ny > 0)
		{
			if (status == 2)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
				nx = -1;
				ny = -1;
			}
			else if (status == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
				nx = 1;
				ny = 1;
			}
		}
		else if (nx * ny < 0)
		{
			if (status == 2)
			{
				SetState(SIMON_STATE_STAIR_DOWN);
				nx = 1;
				ny = -1;
			}
			else if (status == 1)
			{
				SetState(SIMON_STATE_STAIR_UP);
				nx = -1;
				ny = 1;
			}
		}
	}
}

void Simon::AddEnergy(int energy)
{
	SetEnergy(GetEnergy() + energy);
}

void Simon::StartThrowing()
{
	for (int i = 0; i < numberofweapon; i++)
		if (!weapons[i]->IsEnable() && (energy - weapons[i]->GetUseEnergy() >= 0))
		{
			energy -= weapons[i]->GetUseEnergy();
			IsThrowing[i] = true;
			throw_start = GetTickCount();
			break;
		}
}
void Simon::ResetAnimation()
{
	resetAni(SIMON_ANI_FIGHT_LEFT);
	resetAni(SIMON_ANI_FIGHT_RIGHT);
	resetAni(SIMON_ANI_SIT_FIGHT_LEFT);
	resetAni(SIMON_ANI_SIT_FIGHT_RIGHT);
}
void Simon::UpgradeMorningstar()
{
	SetTypeOfMorningstar(GetTypeOfMorningstar() + 1);
}
void Simon::IncreaseWeapon()
{
	SetNumberOfWeapon(GetNumberOfWeapon() + 1);
}
void Simon::SetNumberOfWeapon(int number)
{
	numberofweapon = number;
}
void Simon::SetTypeOfWeapon(int type)
{
	for (int i = 0; i < 3; i++)
	{
		switch (type)
		{

		case ITEM_HOLY_WATER:
			weapons[i] = holywater[i];
			currentWeapon = type;
			break;
		case ITEM_AXE:
			weapons[i] = axe[i];
			currentWeapon = type;
			break;
		case ITEM_DAGGER:
			weapons[i] = dagger[i];
			currentWeapon = type;
			break;
		case ITEM_BOOMERANG:
			weapons[i] = boomerang[i];
			currentWeapon = type;
			break;
			case ITEM_STOP_WATCH:
				weapons[i] = stopwatch[i];
				currentWeapon = type;
				break;
		default:
			break;
		}
	}
}
int Simon::GetScore()
{
	return Enemy::GetScore();
}

void Simon::SetEnergy(int energy)
{
	this->energy = energy;
}

void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x + SIMON_BBOX_WIDTH / 4;
	top = y+4;
	right = left + SIMON_BBOX_WIDTH / 2;
	bottom = top + 60;
	if (IsJump == true)
	{
		top = y + 20;
		bottom = top + 44;
	}
}

void Simon::SetTypeOfMorningstar(int type)
{
	this->type = type;
}

Simon::Simon()
{

	this->AddAnimation(6001);
	this->AddAnimation(6002);
	this->AddAnimation(6003);
	this->AddAnimation(6004);
	this->AddAnimation(6005);
	this->AddAnimation(6006);
	this->AddAnimation(6007);
	this->AddAnimation(6008);
	this->AddAnimation(6009);
	this->AddAnimation(6010);
	this->AddAnimation(6011);
	this->AddAnimation(6012);
	this->AddAnimation(6013);
	this->AddAnimation(6014);
	this->AddAnimation(6015);
	this->AddAnimation(6016);
	this->AddAnimation(6017);
	this->AddAnimation(6018);
	this->AddAnimation(6019);
	this->AddAnimation(6020);
	this->AddAnimation(6021);


	morningstar = new MorningStar();
	life = 3;
	status = SIMON_ALIVE;
	untouchable = 0;
	IsFighting = false;
	IsJump = false;
	IsSit = false;
	type = MORNINGSTAR;
	hp = 16;
	energy = 35;
	numberofweapon = 1;
	for (int i = 0; i < 3; i++)
	{
		dagger[i] = new Dagger();
		boomerang[i] = new Boomerang();
		axe[i] = new Axe();
		holywater[i] = new HolyWater();
		stopwatch[i] = new StopWatch();
		weapons[i] = dagger[i];

	}
}
Simon::~Simon()
{

}
