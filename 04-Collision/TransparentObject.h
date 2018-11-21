#pragma once
#include "GameObject.h"

class TransparentObject:public CGameObject
{
	CSprite *sprite;
	int width;
	int height;
public:
	void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	TransparentObject(int width, int height);
	~TransparentObject();
};

