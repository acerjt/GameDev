#pragma once
#include "GameObject.h"


#define BAT_ST_BBOX_WIDTH  32
#define BAT_ST_BBOX_HEIGHT 32


class Batstartgame : public CGameObject
{
	
	//int untouchable;
	//DWORD untouchable_start;
public:

	virtual void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	//virtual void Render(Camera *camera);
	Batstartgame();
	~Batstartgame();
};

