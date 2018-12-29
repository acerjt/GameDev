#pragma once

#include "Camera.h"
#include "Textures.h"
#include "Sprites.h"
class ColliderEffect
{
	int x, y;
	DWORD timeDelay;
	bool isEnable;
	vector<LPANIMATION> animation;
public:
	void Render(Camera *camera);
	void Update(DWORD dt);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetEnable(bool isenable) { isEnable = isenable; }
	ColliderEffect();
	~ColliderEffect();
};

