#pragma once
#include "GameObject.h"


#define SCENE_LIVE_TIME 7000

#define SCENE_BBOX_WIDTH  0
#define SCENE_BBOX_HEIGHT 0
class Scenes : public CGameObject
{
	CSprite *sprite;
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Scenes();
	~Scenes();
};

