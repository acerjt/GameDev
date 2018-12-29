#pragma once
#include "GameObject.h"


class StartKeyObject:public CGameObject
{
private: 
	DWORD TimeDisplay;
	CSprite *sprite;
public:
	void Update(DWORD dt);
	void Render(Camera *camera);
	void Render();
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	StartKeyObject(int width,int height);
	~StartKeyObject();
};

