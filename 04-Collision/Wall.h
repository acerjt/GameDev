#pragma once
#include "GameObject.h"

#define WALL_BBOX_WIDTH  16
#define WALL_BBOX_HEIGHT 16

class Wall:public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Wall();
	~Wall();
};

