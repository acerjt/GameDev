#include "Dagger.h"
#include "Enemy.h" 
#include "Simon.h"
#include "Torch.h"
#include "Candle.h"
void Dagger::Update(int t, DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<Enemy *>(coObjects->at(i))) {

			Enemy*enemy = dynamic_cast<Enemy *>(coObjects->at(i));

			float l1, t1, r1, b1, l2, t2, r2, b2;
			GetBoundingBox(l1, t1, r1, b1);
			enemy->GetBoundingBox(l2, t2, r2, b2);

			if (t1 <= b2 && b1 >= t2 && l1 <= r2 && r1 >= l2) {
				if ((coObjects->at(i))->nx != 0)
				{
					if (enemy->isEnable != false) {
						enemy->SetHP(enemy->GetHP() - this->damage);
						Simon::IsThrowing[t] = false;
						enemy->GetColliderEffect()->SetEnable(true);
						isEnable = false;
					}	
				}
			}

		}
	}
}

void Dagger::Render(Camera * camera)
{
	Weapons::Render(camera);
}

void Dagger::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (nx > 0)
	{
		left = x;
		top = y;
		right = x + 32;
		bottom = y + 18;
	}
	else
	{
		left = x-32;
		top = y;
		right = left +32;
		bottom = y + 18;
	}
}
void Dagger::SetPosition(float &x, float &y)
{
	CGameObject::SetPosition(x, y);
	x += SIMON_BBOX_WIDTH / 2;
}
Dagger::Dagger()
{
	this->AddAnimation(14001);
	this->AddAnimation(14002);
	useEnergy = 1;
	damage = 1;
}


Dagger::~Dagger()
{
}
