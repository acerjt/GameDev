#pragma once
#include "GameObject.h"
class MapCollision:public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	MapCollision(int width, int height);
	~MapCollision();
};

