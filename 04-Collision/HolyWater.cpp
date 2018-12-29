#include "HolyWater.h"
#include "Brick.h"
#include "Enemy.h"
#include "Simon.h"
#include "PhantomBat.h"

void HolyWater::Update(int t,DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (IsFiring == true)
	{
		vy = 0;
		vx = 0;
	}
	if (isEnable == true)
		vy += 0.000900 * dt;

	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<CBrick *>(coObjects->at(i)))
		{
			CBrick *brick = dynamic_cast<CBrick *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			brick->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				IsFiring = true;
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
					if (enemy->isEnable != false) {
						if (dynamic_cast<PhantomBat *>(coObjects->at(i)))
							isEnable = false;
						vx = 0;
						enemy->SetHP(enemy->GetHP() - this->damage);
						enemy->GetColliderEffect()->SetEnable(true);
						Simon::IsThrowing[t] = false;
						//ResetAnimation();
					}
					//isEnable = false;
				}
			}

		}
	}

	if (IsFiring == true)
	{
		timefiring += dt;
		if (timefiring > 1000)
		{
			IsFiring = false;
			isEnable = false;
			vy = -0.4;
			timefiring = 0;
		}
	}
	if (isEnable == false)
		IsFiring = false;
	
}

void HolyWater::Render(Camera * camera)
{
	Weapons::Render(camera);
	if (IsFiring == true)
		animations[2]->Render(camera, x, y);
	
}

void HolyWater::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x+32;
	bottom = y+25 ;
}

void HolyWater::SetPosition(float & x, float & y)
{
}

HolyWater::HolyWater()//:Weapons(2)
{
	this->AddAnimation(17001);
	this->AddAnimation(17002);
	this->AddAnimation(17003);
	useEnergy = 1;
	damage = 2;
	vy = -0.4;
}


HolyWater::~HolyWater()
{
}
