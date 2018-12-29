#include "StairCheckObject.h"



void StairCheckObject::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_TRANSPARENT);
	sprite->Draw(camera, x, y);
	RenderBoundingBox(camera);
}


void StairCheckObject::GetBoundingBox(float &l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x +width;
	b = y +height;
}

StairCheckObject::StairCheckObject()
{
}



StairCheckObject::~StairCheckObject()
{
}
