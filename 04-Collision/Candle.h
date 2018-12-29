#pragma once
#include "GameObject.h"
#define CANDLE_BBOX_WIDTH  16
#define CANDLE_BBOX_HEIGHT 32
class Candle:public CGameObject
{
public:
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Candle();
	~Candle();
};

