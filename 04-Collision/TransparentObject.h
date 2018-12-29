#pragma once
#include "GameObject.h"

class TransparentObject:public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	TransparentObject(int width, int height);
	~TransparentObject();
};

