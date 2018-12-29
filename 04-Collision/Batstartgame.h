#pragma once
#include "GameObject.h"
class Batstartgame : public CGameObject
{
	CAnimation * getframe;
	int ani;
public:
	void Update(DWORD dt);
	void Render(Camera *camera);
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	Batstartgame();
	~Batstartgame();
	int GetCurrentFrameOfBatstartgame();
	void SetAnimation(int ani) { this->ani = ani; }
	int GetAnimation() { return ani; }
};

