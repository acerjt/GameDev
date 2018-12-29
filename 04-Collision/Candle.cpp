#include "Candle.h"



void Candle::Render(Camera * camera)
{
	CGameObject::Render(camera);
	if (this->isEnable == true)
	{
		animations[0]->Render(camera, x, y);
	}
	
}


void Candle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}


Candle::Candle()
{
	this->AddAnimation(11001);
}


Candle::~Candle()
{
}
