#pragma once
#include "GameObject.h"
class WaterEffect:public CGameObject
{
private:
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	WaterEffect();
	~WaterEffect();
};

