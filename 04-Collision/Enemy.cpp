#include "Enemy.h"
#include "Brick.h"
int Enemy::score = 0;
float Enemy::stopTime = 0;
int Enemy::timestop = 0;
DWORD Enemy::timestop_start = 0;
bool Enemy::IsStop = false;
void Enemy::AddScore()
{
	Enemy::score += point;
}

int Enemy::GetScore()
{
	return score;
}


Enemy::Enemy()
{
}
Enemy::Enemy(int hp)
{
	this->hp = hp;
	this->respawnTime = 1000;
	hpC = hp;
	e_prevHP = hp;
}

Enemy::~Enemy()
{
}


void Enemy::Render(Camera * camera)
{
	CGameObject::Render(camera);
}

void Enemy::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	if(!IsStop)
		CGameObject::Update(dt, coObjects);
	if (!isDead)
	{
		if (isEnable == true)
		{
			respawnTime = 0;
			if (hp < e_prevHP) {
				e_prevHP = hp;
			}

			if (hp <= 0)
			{
				isDead = true;
				isEnable = false;
				GetDeadEffect()->SetEnable(true);
				AddScore();
				return;
			}
			if (IsStop == true) {
			
				if (GetTickCount() - timestop_start > 5000)
				{
					IsStop = false;
					timestop = 0;
					timestop_start = 0;
				}		
			}
		}
		
	}
	 if(!isEnable)
		respawnTime += dt;
}

void Enemy::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
}


void Enemy::Reload()
{
	isEnable = false;
	isDead = true;
	hp = hpC;
	e_prevHP = hp;
}

void Enemy::Respawn()
{
	isEnable = true;
	isDead = false;
	hp = hpC;
	e_prevHP = hp;
}

void Enemy::SetScore(int score)
{
	Enemy::score += score;
}



