#include "MapCollision.h"



void MapCollision::Render(Camera * camera)
{

	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(ID_TEX_TRANSPARENT);
	sprite->Draw(camera, x,y);
}

void MapCollision::Render()
{
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
	/*CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	textures->Add(ID_TEX_TRANSPARENT, L"textures\\transparent.png", D3DCOLOR_XRGB(237, 28, 36));
	sprites->Add(5001, 0, 0, 31, 31, textures->Get(ID_TEX_TRANSPARENT));*/

	this->width = width;
	this->height = height;
}


MapCollision::~MapCollision()
{
}
