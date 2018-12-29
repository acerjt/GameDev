#include "PhantomBat.h"

void PhantomBat::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (anirender == 1)
	{
		ani = animations[1];
		if (ani->getCurrentFrame() == 0)
		{
			left = x;
			right = x + 96;	
		}
		else if (ani->getCurrentFrame() == 1)
		{
			left = x + 18;
			right = left + 64;
		}
		top = y;
		bottom = top + 46;
	}
}

void PhantomBat::Update(DWORD dt)
{
	if (isEnable == true)
	{
		if (Intro(dt) == true)
			return;	
		CheckHPChange();
		if (isHurted == true) 
			CheckHurtTime(dt);
		else
		{
			if (isFlytosimonpos == true) {
				if (waitTime > 0)
					waitTime -= dt;
				else
				{
					Fly(dt);
				}
			}
			else if (isFlytosimonpos == false) {
				if (isFlytorandompos == false)
					FlyToRandomPos(dt);
				else if(isFlytorandompos == true)
					RandomPos();
			}
		}
	}
	if (!isEnable)
	{
		delayTime += dt;
		if(delayTime>1500)
			deadeffect->Update(dt);
	}
	collider->SetPosition(x, y + 10);
	collider->Update(dt);
}

void PhantomBat::Render(Camera * camera)
{
	if (state == PHANTOM_BAT_STATE_IDLE)
		anirender = 0;
	else if (state == PHANTOM_BAT_STATE_MOVE)
		anirender = 1;
	if (isEnable)
		animations[anirender]->Render(camera, x, y);
	Enemy::Render(camera);
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, 0);
	for (int j = 0; j < 2 ; j++)
	{
		pos.y = y + 44 * j;
		for (int i = 0; i < 3; i++)
		{
			pos.x = x + 30 * i;
				this->GetDeadEffect()->Render(camera,pos);
		}
	}
}

void PhantomBat::Render()
{
}

void PhantomBat::SetState(int state)
{
	CGameObject::SetState(state);
}

void PhantomBat::CalculateSimonPos(Simon * simon, DWORD dt)
{
 	if (simonPos.x < 0) {
		simonPos = D3DXVECTOR2(simon->GetPosition().x, simon->GetPosition().y);
	}
	else if (chaseTime > 0) {
		chaseTime -= dt*0.001;
		simonPos = D3DXVECTOR2(simon->GetPosition().x, simon->GetPosition().y);
	}
	
	if (isFlytosimonpos == true)
	{
		distance = sqrt(
			pow(simonPos.x - GetPosition().x, 2) +
			pow(simonPos.y - GetPosition().y, 2));

		nx = (simonPos.x - GetPosition().x) / distance;
		ny = (simonPos.y - GetPosition().y) / distance;
	}
	if (isFlytosimonpos == false)
	{
		batPos= D3DXVECTOR2(GetPosition().x,GetPosition().y);
	}
}


void PhantomBat::Fly(DWORD dt)
{
	if (abs(batPos.x - simonPos.x) > 200)
	{
		vx = 0.23;
		vy = 0.18;
	}
	x += nx * vx * dt;
	y += ny * vy * dt;
	
	if (sqrt(pow(simonPos.x - GetPosition().x, 2) + pow(simonPos.y - GetPosition().y, 2)) >= distance)
	{
		isFlytosimonpos = false;	
		x = simonPos.x; 
		y = simonPos.y;
	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_MOVE);
}



void PhantomBat::RandomPos()
{
	random.x = rand() % (400) +5100;
	random.y = rand() % (50) +120 ;
	isFlytorandompos = false;
	waitTime = WAIT_TIME;
	vx = 0.125;
	vy = 0.12;
}

bool PhantomBat::Intro(DWORD dt)
{
	if (introTime > 0) 
	{
		if (introTime > 1500)
			SetState(PHANTOM_BAT_STATE_IDLE);
		else
			SetState(PHANTOM_BAT_STATE_MOVE);
		introTime -= dt;
		return true;
	}
	else
		return false;
}

void PhantomBat::CheckHPChange()
{
	if (previousHP != hp)
	{
		if (hp <= 0) 
		{
			
			isEnable = false;
			isDead = true;
			GetDeadEffect()->SetEnable(true);
			return;
		}
		else 
		{
			isHurted = true; 
			previousHP = hp; 					 
			return;
		}
	}
}

void PhantomBat::CheckHurtTime(DWORD dt)
{
	SetState(PHANTOM_BAT_STATE_HURT);  
	hurtTime -= dt; 
	if (hurtTime <= 0) 
	{
		isHurted = false; 
		hurtTime = HURT_TIME; 
	}
}

void PhantomBat::FlyToRandomPos(DWORD dt)
{
	distance = sqrt(
		pow(random.x - GetPosition().x, 2) +
		pow(random.y - GetPosition().y, 2));
	nx = (random.x- GetPosition().x ) / distance;
	ny = (random.y- GetPosition().y  ) / distance;
	x += nx * vx * dt;
	y += ny * vy * dt;;
	if (sqrt(pow( x- random.x , 2) + pow( y - random.y , 2)) >= distance)
	{
		vx = 0.17;
		vy = 0.17;
		chaseTime = CHASE_TIME;

		isFlytosimonpos = true;
		isFlytorandompos = true;
		x = random.x; 
		y = random.y;
		
	}
	this->SetPosition(x, y);
	SetState(PHANTOM_BAT_STATE_MOVE);
}

PhantomBat::PhantomBat():Enemy(16)
{
	this->AddAnimation(25001);
	this->AddAnimation(25002);
	damage = 3;
	point = 3000;
	srand(time(0));
	isFlytorandompos = true;
	isFlytosimonpos = true;
	waitTime = 0;
	hurtTime = HURT_TIME;
	isHurted = false;
	vx = 0.125;
	vy = 0.120;
	nx = 0;
	ny = 0;
	SetState(PHANTOM_BAT_STATE_IDLE);
	previousHP = hp;
	introTime = 2000;
	simonPos.x = -1;
	distance = -1;
}


PhantomBat::~PhantomBat()
{
}
