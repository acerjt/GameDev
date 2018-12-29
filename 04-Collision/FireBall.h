#pragma once
#include "GameObject.h"

#define FIRE_BALL_BBOX_WIDTH  14
#define FIRE_BALL_BBOX_HEIGHT 12

#define FIRE_BALL_SPEED 0.08

class FireBall:public CGameObject
{
	CSprite *sprite;
	int damage;
public:
	void Update(DWORD dt);
	void Render(Camera *camera);
	void SetDamage(int damage) { this->damage = damage; }
	int GetDamage() { return damage; }
	void GetBoundingBox(float &l, float &t, float &r, float &b);
	FireBall();
	~FireBall();
};

