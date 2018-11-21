#pragma once
#include "GameObject.h"
class Castle:public CGameObject
{
	CSprite *sprite;
public:
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	Castle();
	~Castle();
};

