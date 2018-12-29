#pragma once
#include "GameObject.h"
class Stair: public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Stair();
	~Stair();
};

