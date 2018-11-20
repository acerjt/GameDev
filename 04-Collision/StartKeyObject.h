#pragma once
#include "GameObject.h"

#define START_KEY_BBOX_WIDTH  222
#define START_KEY_BBOX_HEIGHT 14
class StartKeyObject:public CGameObject
{
private: 
	int TimeDisplay;

public:
	void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	StartKeyObject();
	~StartKeyObject();
};

