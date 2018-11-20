#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32
class CBrick : public CGameObject
{
	CSprite *sprite;
	int chose;
protected:
	int width;
	int height;
public:
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBrick(int width,int height,int chose);
};