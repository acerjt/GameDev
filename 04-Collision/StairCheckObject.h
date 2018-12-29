#pragma once
#include "GameObject.h"
class StairCheckObject:public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	StairCheckObject();
	~StairCheckObject();
};

