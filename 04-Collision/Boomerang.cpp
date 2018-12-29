#include "Boomerang.h"
#include "Simon.h"
#include "Enemy.h"
#include "PhantomBat.h"

void Boomerang::Update(int t,DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy *>(coObjects->at(i)) ) {
			Enemy*enemy = dynamic_cast<Enemy *>(coObjects->at(i));
			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);
			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						if (dynamic_cast<PhantomBat *>(coObjects->at(i)) && count == 0)
						{
							
							enemy->SetHP(enemy->GetHP() - damage);
							enemy->GetColliderEffect()->SetEnable(true);
							count = 1;
						}
						else if (!(dynamic_cast<PhantomBat *>(coObjects->at(i))))
						{
							enemy->SetHP(enemy->GetHP() - damage);
							enemy->GetColliderEffect()->SetEnable(true);
							Simon::IsThrowing[t] = false;
						}
					}
				}
			}
		}
	}

}

void Boomerang::Render(Camera * camera)
{
	Weapons::Render(camera);
	if (this->isEnable == false)
		count = 0;
}

void Boomerang::SetState(int state)
{
}

void Boomerang::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + 28;
	bottom = y + 28;
}

void Boomerang::SetPosition(float & x, float & y)
{
}

Boomerang::Boomerang()
{
	this->AddAnimation(15001);
	this->AddAnimation(15002);
	useEnergy = 1;
	damage = 2;
}


Boomerang::~Boomerang()
{
}
