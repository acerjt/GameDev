#include "WaterEffect.h"



void WaterEffect::Render(Camera * camera)
{
	CSprites * sprites = CSprites::GetInstance();
	sprite = sprites->Get(27001);
	sprite->Draw(camera, x, y);
}

void WaterEffect::GetBoundingBox(float & l, float & t, float & r, float & b)
{
}


WaterEffect::WaterEffect()
{

}


WaterEffect::~WaterEffect()
{
}
