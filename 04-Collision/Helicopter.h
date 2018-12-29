#pragma once
#include "GameObject.h"


#define HELICOPTER_SPEED 0.05f
#define HELICOPTER_BBOX_WIDTH 512
#define HELICOPTER_BBOX_HEIGHT 448
class Helicopter: public CGameObject
{
public:
	void Update(DWORD dt);
	void Render(Camera *camera);
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	Helicopter();
	~Helicopter();
};

