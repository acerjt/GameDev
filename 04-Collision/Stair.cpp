#include "Stair.h"



void Stair::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	switch (type)
	{
	case 131:
		sprite = sprites->Get(13001);
		sprite->Draw(camera, x, y);
		break;
	case 13:
		sprite = sprites->Get(13002);
		sprite->Draw(camera, x, y);
		break;
	}
}



void Stair::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}

Stair::Stair()
{

}


Stair::~Stair()
{
}
