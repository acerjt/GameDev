#pragma once
#include "GameObject.h"

#define DOOR_BBOX_WIDTH  16
#define DOOR_BBOX_HEIGHT 96

class Door:public CGameObject
{
	int anirender;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void SetAnimation(int anirender);
	Door();
	~Door();
};

