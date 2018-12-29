#pragma once
#include "Weapons.h"
class Axe:public Weapons
{
public:
	void Update(int t, DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
	Axe();
	~Axe();
};

