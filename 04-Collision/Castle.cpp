#include "Castle.h"



void Castle::Render(Camera * camera)
{
	if (this->isEnable == true)
	{
		CSprites * sprites = CSprites::GetInstance();
		sprite = sprites->Get(10001);
		sprite->Draw(camera, x, y);
	}
}

void Castle::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = t = r = b = 0;
}

Castle::Castle()
{

}


Castle::~Castle()
{
}
