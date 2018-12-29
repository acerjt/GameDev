#include "TransparentObject.h"


void TransparentObject::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_TRANSPARENT);
	if (isEnable == true)
	{
		sprite->Draw(camera, x, y);
	}
	RenderBoundingBox(camera);
}


void TransparentObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + width;
	b = t + height;
}

TransparentObject::TransparentObject(int width,int height)
{
	this->width = width;
	this->height = height;
}
TransparentObject::~TransparentObject()
{


}
