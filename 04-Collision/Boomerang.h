#pragma once
#include "Weapons.h"
class Boomerang: public Weapons
{
public:
	void Update(int t,DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
	void SetState(int state);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
	Boomerang();
	~Boomerang();
};

