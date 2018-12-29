#pragma once
#include "Camera.h"
#include "Textures.h"
#include "Sprites.h"
class DeadEffect
{
	float x, y;
	DWORD timeDelay;
	bool isEnable;
	vector<LPANIMATION> animation;
public:
	void Render(Camera *camera);
	void Render(Camera * camera, D3DXVECTOR3 &pos);
	void Update(DWORD dt);
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetEnable(bool isenable) { isEnable = isenable; }
	DeadEffect();
	~DeadEffect();
};

