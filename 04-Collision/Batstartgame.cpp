#include "Batstartgame.h"


void Batstartgame::Update(DWORD dt)
{
	if (ani == 0)
	{
		getframe = animations[0];
		if (getframe->getCurrentFrame() == 12)
			ani = 1;
	}
}


void Batstartgame::Render(Camera *camera)
{

	animations[ani]->Render(camera,x, y);
}

Batstartgame::Batstartgame():CGameObject()
{
	this->AddAnimation(2001);
	this->AddAnimation(2002);
}
Batstartgame::~Batstartgame()
{
}

int Batstartgame::GetCurrentFrameOfBatstartgame()
{
	getframe = animations[ani];
	return getframe->getCurrentFrame();
}

void Batstartgame::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = t = r = b = 0;
}



