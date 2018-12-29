#include "HP.h"



void HP::Render(Camera * camera)
{
}

void HP::Render()
{
	CSprites * sprites = CSprites::GetInstance();
	switch (chose)
	{
	case 1:
		sprite=sprites->Get(12001);
		sprite->Draw(x,y);
		break;
	case 2:
		sprite = sprites->Get(12002);
		sprite->Draw(x, y);
		sprite->Draw(x, y+20);
		break;
	case 3:
		sprite = sprites->Get(12003);
		sprite->Draw(x, y);
		break;
	}
}

void HP::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

void HP::Update(DWORD dt)
{
}

HP::HP(int chose)
{
	this->chose = chose;
}


HP::~HP()
{
}
