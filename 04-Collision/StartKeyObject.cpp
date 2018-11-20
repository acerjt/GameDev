#include "StartKeyObject.h"



void StartKeyObject::Render(Camera * camera)
{
	
	if (isEnable != true)
		RenderBoundingBox(camera);
}

void StartKeyObject::Render()
{
	int x = 1;
}

void StartKeyObject::Update(DWORD dt)
{
	CGameObject::Update(dt);
	TimeDisplay += dt;
	if (TimeDisplay >= 300)
	{
		isEnable = !isEnable;
		TimeDisplay -= 300;
	}
}

void StartKeyObject::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x;
	t = y;
	r = x + START_KEY_BBOX_WIDTH;
	b = y + START_KEY_BBOX_HEIGHT;
}

StartKeyObject::StartKeyObject()
{
	TimeDisplay = 0;
}


StartKeyObject::~StartKeyObject()
{
}
