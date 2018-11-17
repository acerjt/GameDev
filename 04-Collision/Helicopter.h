#pragma once
#include "GameObject.h"


#define HELICOPTER_SPEED 0.05f
#define HELICOPTER_BBOX_WIDTH 512
#define HELICOPTER_BBOX_HEIGHT 448
class Helicopter: public CGameObject
{
public:
	//virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	Helicopter();
	~Helicopter();
};

