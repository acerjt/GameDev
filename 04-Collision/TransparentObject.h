#pragma once
#include "GameObject.h"

#define TRANSPARENT_OBJECT_BBOX_WIDTH  32
#define TRANSPARENT_OBJECT_BBOX_HEIGH  32
class TransparentObject:public CGameObject
{
	CSprite *sprite;
public:
	void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	TransparentObject();
	~TransparentObject();
};

