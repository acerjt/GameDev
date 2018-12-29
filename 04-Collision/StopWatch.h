#pragma once
#include "Weapons.h"
class StopWatch:public Weapons
{
public:
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	StopWatch();
	~StopWatch();
};

