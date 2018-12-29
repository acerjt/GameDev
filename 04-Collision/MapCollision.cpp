#include "MapCollision.h"



void MapCollision::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_TRANSPARENT);
	sprite->Draw(camera, x,y);
}


void MapCollision::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

MapCollision::MapCollision(int width, int height)
{
	this->width = width;
	this->height = height;
}


MapCollision::~MapCollision()
{
}
