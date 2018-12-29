#include "Helicopter.h"

void Helicopter::Update(DWORD dt)
{
	CGameObject::Update(dt);
	vx = -HELICOPTER_SPEED;
	x += dx;
}
void Helicopter::Render(Camera *camera)
{
	animations[0]->Render(camera,x, y);
}
void Helicopter::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = top = right = bottom = 0;
}

Helicopter::Helicopter()
{
	this->AddAnimation(3001);
}

Helicopter::~Helicopter()
{
}
