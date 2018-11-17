#pragma once
#include "GameObject.h"

#define TORCH_BBOX_WIDTH  32
#define TORCH_BBOX_HEIGHT 64

#define TORCH_STATE_1 100
#define TORCH_STATE_2 200



class Torch :public CGameObject
{

public:
	virtual void Render(Camera *camera);
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state) { this->state = state; };
	/*virtual void Render(Camera *camera);*/
	Torch();
	~Torch();
};

