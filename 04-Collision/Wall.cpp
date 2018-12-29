#include "Wall.h"



void Wall::Render(Camera * camera)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x, y, 0);
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(20001);
	for (int j = 0; j < height / WALL_BBOX_HEIGHT; j++)
	{
		pos.y = y + WALL_BBOX_HEIGHT * j;
		for (int i = 0; i < width / WALL_BBOX_WIDTH; i++)
		{
			pos.x = x + WALL_BBOX_WIDTH * i;
			if(isEnable)
				sprite->Draw(camera, pos);
		}
	}
}


void Wall::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

Wall::Wall()
{
}


Wall::~Wall()
{
	
}
