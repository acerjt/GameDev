#include "Axe.h"
#include "Brick.h"
#include "Simon.h"
#include "Enemy.h"


void Axe::Update(int t, DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	if(isEnable==true)
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
				vy = -0.4;
				isEnable = false;
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
						enemy->SetHP(enemy->GetHP() - damage);
						enemy->GetColliderEffect()->SetEnable(true);
						Simon::IsThrowing[t] = false;
					}
					isEnable = false;
				}
			}
		}
	}
}

void Axe::Render(Camera * camera)
{
	Weapons::Render(camera);
}

void Axe::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 30;
	bottom =y + 28;
}

void Axe::SetPosition(float & x, float & y)
{
}

Axe::Axe()
{
	this->AddAnimation(16001);
	this->AddAnimation(16002);
	useEnergy = 1;
	damage = 2;
	vy = -0.4;
}


Axe::~Axe()
{
}
