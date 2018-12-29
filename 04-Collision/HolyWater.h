#pragma once
#include "Weapons.h"
class HolyWater:public Weapons
{
protected:
	int anirender;
	bool IsFiring;
	DWORD timefiring;
public:
	void Update(int t,DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void SetPosition(float &x, float &y);
	bool IsFire() { return IsFiring; }
	HolyWater();
	~HolyWater();
};

