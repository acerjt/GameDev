#pragma once
#include "GameObject.h"
class HP :public CGameObject
{
	int chose;
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	void Update(DWORD dt);
	HP(int chose);
	~HP();
};

