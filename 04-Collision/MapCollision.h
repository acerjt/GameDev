#pragma once
#include "GameObject.h"
class MapCollision:public CGameObject
{
	CSprite *sprite;
protected:
	int width;
	int height;
public:
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	/*virtual void Render(Camera *camera);*/
	MapCollision(int width, int height);
	~MapCollision();
};

