#include "Door.h"



void Door::Render(Camera * camera)
{
	if (anirender == 1 && animations[anirender]->getCurrentFrame() == 1)
	{
		anirender = 2;
	}
	if (anirender == 3 && animations[anirender]->getCurrentFrame() == 1)
	{
		anirender = 0;
	}
	animations[anirender]->Render(camera, x, y);
	//RenderBoundingBox(camera);
}


void Door::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if (anirender == 0)
	{
		l = x;
		t = y;
		r = x + DOOR_BBOX_WIDTH;
		b = y + DOOR_BBOX_HEIGHT;
	}
	
}
void Door::SetAnimation(int anirender)
{
	this->anirender = anirender;
}
Door::Door()
{
	this->AddAnimation(21001);
	this->AddAnimation(21002);
	this->AddAnimation(21003);
	this->AddAnimation(21004);
	anirender = 0;
}


Door::~Door()
{
}
