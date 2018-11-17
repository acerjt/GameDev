#include <algorithm>
#include "debug.h"
#include "Item.h"
#include "Brick.h"
#include "Simon.h"
#include "Game.h"
#include "Zombie.h"
#include "Torch.h"
void Simon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)//, vector<LPGAMEOBJECT> *noncoObjects)
{
	
	 //Calculate dx, dy 
	CGameObject::Update(dt);
		// Simple fall down
		
		 vy += SIMON_GRAVITY * dt;

		 if (dy == 0)
			 IsJump = false;
		if (state != SIMON_STATE_SIT)// && state!=SIMON_STATE_JUMP)
			IsSit = false;
		if (IsFighting)
		{
			morningstar->SetPosition(this->x, this->y,IsSit);
			
	
			if (morningstar->GetCurrentFrameOfMorningStar() == 2)
			{
				morningstar->Update(dt, coObjects);	
			}
	
			if (GetTickCount() - attack_start > SIMON_ATTACK_TIME)
			{
				this->resetAni(SIMON_ANI_FIGHT_LEFT);
				this->resetAni(SIMON_ANI_FIGHT_RIGHT);
				this->resetAni(SIMON_ANI_SIT_FIGHT_LEFT);
				this->resetAni(SIMON_ANI_SIT_FIGHT_RIGHT);
				morningstar->resetAni(0);
				morningstar->resetAni(1);
				morningstar->resetAni(2);
				morningstar->resetAni(3);
				morningstar->resetAni(4);
				morningstar->resetAni(5);
				attack_start = 0;
				IsFighting = false;
			}
		}


		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		//turn off collision when die 
		if (state != SIMON_STATE_DIE)
			CalcPotentialCollisions(coObjects, coEvents);

		//reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = 0;
		}

		
		



		// No collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick *>(e->obj))
				{
					if (e->ny < 0)
					{
						x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
						y += min_ty * dy + ny * 0.4f;

						if (nx != 0) vx = 0;
						if (ny != 0) vy = 0;
					}
				}
				else
				{
					x += dx + nx * 0.4f;
					y += dy + ny * 0.4f;
				}
				if (dynamic_cast<Item *>(e->obj))
				{
					Item *item = dynamic_cast<Item *>(e->obj);
					
						float l1, t1, r1, b1, l2, t2, r2, b2;
						GetBoundingBox(l1, t1, r1, b1);
						item->GetBoundingBox(l2, t2, r2, b2);

						if (t1 <= b2 || b1 >= t2 || l1 <= r2 || r1 >= l2) {

							if (item->isEnable == true) {


								switch (item->itemType)
								{
								case ITEM_SMALL_HEART:
									
									break;
								case ITEM_BIG_HEART:
									
									break;
								case ITEM_ROAST:
								
									break;
								case ITEM_MORNINGSTAR:
									item->UpgradeMorningstar();
									break;
								case ITEM_BALL:
									
									break;
								case ITEM_MONEY:
								
									break;
								case ITEM_INVISIBLE:
									
									break;
								case ITEM_ROSARY:
									
									break;
								case ITEM_UPGRADE_1:
									
									break;
								case ITEM_UPGRADE_2:
								
									break;
								default:
									
									break;
								}

								item->isEnable = false;
								item->isDead = true;
							}
						}
					
				}
				if (dynamic_cast<Zombie *>(e->obj))
				{
					Zombie *zombie = dynamic_cast<Zombie *>(e->obj);

					//jump on top >> kill Goomba and deflect a bit 
					if (e->ny < 0)
					{
						if (zombie->GetState() != ZOMBIE_STATE_DIE)
						{
							zombie->SetState(ZOMBIE_STATE_DIE);
							vy = -SIMON_JUMP_DEFLECT_SPEED;
						}
					}
					else if (e->nx != 0)
					{
						if (untouchable == 0)
						{
							if (zombie->GetState() != ZOMBIE_STATE_DIE)
							{
								if (life > 0)
								{
									life--;
									StartUntouchable();
								}
								else
									SetState(SIMON_STATE_DIE);
							}
						}
					}
				}
			}
		}

		//clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}


void Simon::Render(Camera *camera)
{
	int anirender;
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
					if (type==MORNINGSTAR)
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
				else if ((nx < 0)  && IsFighting)
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
					anirender = SIMON_ANI_IDLE_LEFT;
				else if (nx > 0)
					anirender = SIMON_ANI_IDLE_RIGHT;

			}
			else if (vx>0)
				anirender = SIMON_ANI_WALKING_RIGHT;
			else anirender = SIMON_ANI_WALKING_LEFT;
		}
	if (state == SIMON_STATE_IDLE_2)
		anirender = SIMON_ANI_IDLE_INTRO;

	if (IsJump==true && anirender != SIMON_ANI_FIGHT_LEFT && anirender != SIMON_ANI_FIGHT_RIGHT)
		 if (nx < 0)
			anirender = SIMON_ANI_SIT_JUMP_LEFT;
		else if	(nx > 0)
			anirender = SIMON_ANI_SIT_JUMP_RIGHT;

	int alpha = 255;
	if (untouchable) alpha = 128;
		animations[anirender]->Render(camera, x, y, alpha);

	//RenderBoundingBox(camera);
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
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_JUMP:
		IsJump = true;
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
	}
}



void Simon::MorningStarCheckCollider(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if (IsFighting && morningstar->GetCurrentFrameOfMorningStar() == 2)
	{
			morningstar->RenderBoundingBox(camera);
			morningstar->Update(dt, coObjects);
		//morningstar->CheckCollider(gameTime, listGameObject);
	}
}







void Simon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{

	left = x+ SIMON_BBOX_WIDTH/4;
	top = y;
	right = left + SIMON_BBOX_WIDTH/2;
	bottom = top + SIMON_BBOX_HEIGHT;
}

void Simon::SetTypeOfMorningstar(int type)
{
	this->type = type;
}



Simon::Simon()
{
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_SIMON, L"textures\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 texsimon = textures->Get(ID_TEX_SIMON);
	sprites->Add(6001, 900, 0, 960, 66, texsimon);		// idle right

	sprites->Add(6002, 839, 0, 899, 66, texsimon);		// walk
	sprites->Add(6003, 778, 0, 838, 66, texsimon);
	sprites->Add(6004, 716, 0, 776, 66, texsimon);

	sprites->Add(6005, 0, 0, 60, 66, texsimon);		// idle left

	sprites->Add(6006, 61, 0, 121, 66, texsimon);		// walk
	sprites->Add(6007, 122, 0, 182, 66, texsimon);
	sprites->Add(6008, 183, 0, 243, 66, texsimon);

	sprites->Add(6009, 61, 66, 121, 132, texsimon); //idle_intro

	sprites->Add(6010, 300, 0, 360, 66, texsimon);
	sprites->Add(6011, 361, 0, 421, 66, texsimon);
	sprites->Add(6012, 420, 0, 480, 66, texsimon);

	//sprites->Add(10019, 238, 0, 298, 66, texSimon);  //jump

	sprites->Add(6013, 600, 0, 649, 66, texsimon);
	sprites->Add(6014, 539, 0, 588, 66, texsimon);
	sprites->Add(6015, 480, 0, 540, 66, texsimon);


	sprites->Add(6016, 240, 0, 304, 66, texsimon);


	sprites->Add(6017, 660, 0, 720, 66, texsimon);

	sprites->Add(6018,420, 66,486, 132, texsimon);
	sprites->Add(6019, -1, 132, 62, 198, texsimon);
	sprites->Add(6020, 61, 132, 125, 198, texsimon);

	sprites->Add(6021, 480,66, 540, 132, texsimon);
	sprites->Add(6022, 901, 132, 960, 198, texsimon);
	sprites->Add(6023, 839, 132, 899, 198, texsimon);

	ani = new CAnimation(100);
	ani->Add(6001);
	animations->Add(6001, ani);
	this->AddAnimation(6001);
	ani = new CAnimation(100);
	ani->Add(6002);
	ani->Add(6003);
	ani->Add(6004);
	animations->Add(6002, ani);
	this->AddAnimation(6002);
	ani = new CAnimation(100);
	ani->Add(6005);
	animations->Add(6003, ani);
	this->AddAnimation(6003);
	ani = new CAnimation(100);
	ani->Add(6006);
	ani->Add(6007);
	ani->Add(6008);
	animations->Add(6004, ani);
	this->AddAnimation(6004);
	ani = new CAnimation(100);
	ani->Add(6009);
	animations->Add(6005, ani);
	this->AddAnimation(6005);
	ani = new CAnimation(150);
	ani->Add(6010);
	ani->Add(6011);
	ani->Add(6012);
	animations->Add(6006, ani);
	this->AddAnimation(6006);
	ani = new CAnimation(150);
	ani->Add(6013);
	ani->Add(6014);
	ani->Add(6015);
	animations->Add(6007, ani);
	this->AddAnimation(6007);
	ani = new CAnimation(100);
	ani->Add(6016);
	animations->Add(6008, ani);
	this->AddAnimation(6008);
	ani = new CAnimation(100);
	ani->Add(6017);
	animations->Add(6009, ani);
	this->AddAnimation(6009);
	ani = new CAnimation(150);
	ani->Add(6018);
	ani->Add(6019);
	ani->Add(6020);
	animations->Add(6010, ani);
	this->AddAnimation(6010);
	ani = new CAnimation(150);
	ani->Add(6021);
	ani->Add(6022);
	ani->Add(6023);
	animations->Add(6011, ani);
	this->AddAnimation(6011);

	morningstar = new MorningStar();
	life = 3;
	status = SIMON_ALIVE;
	untouchable = 0;
	IsFighting = false;
	IsJump = false;
	IsSit = false;
	type = MORNINGSTAR;
	//IsSitting = false;
}
Simon::~Simon()
{

}
