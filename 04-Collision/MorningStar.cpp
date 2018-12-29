#include "MorningStar.h"
#include "Zombie.h"
#include "Torch.h"
#include "Candle.h"
#include "Enemy.h"
#include "Simon.h"
#include "Brick.h"
#include "Wall.h"
#include "FireBall.h"
MorningStar::MorningStar()
{
	this->AddAnimation(7001);
	this->AddAnimation(7002);
	this->AddAnimation(7003);
	this->AddAnimation(7004);
	this->AddAnimation(7005);
	this->AddAnimation(7006);
	damage = 1;
}


void MorningStar::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
 	CGameObject::Update(dt);

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Torch *>(coObjects->at(i))) {
			Torch*torch = dynamic_cast<Torch *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			torch->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {

				if (torch->isEnable == true) {
					torch->GetColliderEffect()->SetEnable(true);
					torch->GetDeadEffect()->SetEnable(true);
					torch->isEnable = false;
					torch->isDead = true;
				}
			}
		}
		if (dynamic_cast<Candle *>(coObjects->at(i))) {
			Candle*candle = dynamic_cast<Candle *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			candle->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {

				if (candle->isEnable == true) {
					candle->GetColliderEffect()->SetEnable(true);
					candle->GetDeadEffect()->SetEnable(true);
					candle->isEnable = false;
					candle->isDead = true;
				}
			}
		}
		if (dynamic_cast<CBrick *>(coObjects->at(i))) {
			CBrick*brick = dynamic_cast<CBrick *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			brick->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {

				if (brick->isEnable == true && 
				   (brick->GetType() == -1 )) {
					brick->isEnable = false;
					brick->isDead = true;
					coObjects->erase(coObjects->begin() + i);
				}
			}
		}
		if (dynamic_cast<FireBall *>(coObjects->at(i))) {
			FireBall*fireball = dynamic_cast<FireBall *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			fireball->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {

				if (fireball->isEnable == true) {
					fireball->GetColliderEffect()->SetEnable(true);
					fireball->GetDeadEffect()->SetEnable(true);
					fireball->isEnable = false;
					fireball->isDead = true;
				}
			}
		}
		if (dynamic_cast<Wall *>(coObjects->at(i))) {
			Wall*wall = dynamic_cast<Wall *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			wall->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if (wall->isEnable == true && wall->GetType() == -7) {
					wall->isEnable = false;
					wall->isDead = true;
					coObjects->erase(coObjects->begin() + i);
				}
			}
		}
			if (dynamic_cast<Enemy *>(coObjects->at(i))) {

				Enemy*enemy = dynamic_cast<Enemy *>(coObjects->at(i));

				float l1, t1, r1, b1, l2, t2, r2, b2;
				GetBoundingBox(l1, t1, r1, b1);
				enemy->GetBoundingBox(l2, t2, r2, b2);
				
				if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
					if ((coObjects->at(i))->nx != 0)
					{
						enemy->GetColliderEffect()->SetEnable(true);
						if (enemy->isEnable != false) {
							enemy->SetHP(enemy->GetHP() - this->damage);
							Simon::IsFighting = false;
							ResetAnimation();
						}
					}
				}

			}
	}
}
void MorningStar::ResetAnimation()
{
	resetAni(0);
	resetAni(1);
	resetAni(2);
	resetAni(3);
	resetAni(4);
	resetAni(5);
}
int MorningStar::GetCurrentFrameOfMorningStar()
{
	if (anirender == MORNINGSSTAR_ANI_RIGHT)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT];
	}
	if (anirender == MORNINGSSTAR_ANI_RIGHT_1)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT_1];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_1)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT_1];
	}
	if (anirender == MORNINGSSTAR_ANI_RIGHT_2)
	{
		ani = animations[MORNINGSSTAR_ANI_RIGHT_2];
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_2)
	{
		ani = animations[MORNINGSSTAR_ANI_LEFT_2];
	}
	return ani->getCurrentFrame();
}


void MorningStar::SetPosition(float x,float y,bool Issit)
{

	if (Issit == true)
	{
		if(nx<0)
		x -= MORNINGSTAR_SET_POSITION_X_1;
		else
			x -= MORNINGSTAR_SET_POSITION_X;
		y += MORNINGSTAR_SET_POSITION_Y;
	}
	else
		x -= MORNINGSTAR_SET_POSITION_X;
	CGameObject::SetPosition(x, y);
}

void MorningStar::Render(Camera *camera)
{
	
}

void MorningStar::Render(Camera *camera,int ani)
{
	if (isEnable == true)
	{
		anirender = ani;
		animations[ani]->Render(camera, x, y);
	}
}


void MorningStar::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	if (anirender == MORNINGSSTAR_ANI_RIGHT)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT)
	{
		left = x+ MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_RIGHT_1)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_1_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_1_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_1)
	{
		left = x + MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_1_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_1_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_1_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_RIGHT_2)
	{
		left = x + MORNINGSTAR_SET_POSITION_X + SIMON_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_2_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_2_BBOX_HEIGHT;
	}
	else if (anirender == MORNINGSSTAR_ANI_LEFT_2)
	{
		left = x + MORNINGSTAR_SET_POSITION_X - MORNINGSTAR_2_BBOX_WIDTH;
		top = y + MORNINGSTAR_SET_POSITION_BOUNDINGBOX_Y;
		right = left + MORNINGSTAR_2_BBOX_WIDTH;
		bottom = y + MORNINGSTAR_2_BBOX_HEIGHT;
	}



}


MorningStar::~MorningStar()
{
}
