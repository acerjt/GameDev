#include "TransparentObject.h"



void TransparentObject::Update(DWORD dt)
{
}

void TransparentObject::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_TRANSPARENT);
	if (isEnable == true)
	{
		sprite->Draw(camera, x, y);
	}
}

void TransparentObject::Render()
{
}

void TransparentObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = l + TRANSPARENT_OBJECT_BBOX_WIDTH;
	b = t + TRANSPARENT_OBJECT_BBOX_HEIGH;
}

TransparentObject::TransparentObject()
{

}


TransparentObject::~TransparentObject()
{


}
