#pragma once
#include "GameObject.h"


class Batstartgame : public CGameObject
{
	
	CAnimation * getframe;
public:
	int ani;
public:

	virtual void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	//virtual void Render(Camera *camera);
	Batstartgame();
	~Batstartgame();
	int GetCurrentFrameOfBatstartgame();
};

