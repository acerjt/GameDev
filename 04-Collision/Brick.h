#pragma once
#include "GameObject.h"
#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 32
class CBrick : public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	CBrick();
};