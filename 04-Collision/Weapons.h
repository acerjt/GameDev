#pragma once
#include "GameObject.h"
#define RIGHT	1
#define LEFT	-1
class Weapons : public CGameObject
{
protected:
	int useEnergy;
	int damage;
	int count;
public:
	Weapons();
	~Weapons();
	void resetAni(int aniID) { animations[aniID]->reset(); }
	void Update(int t, DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void ResetAnimation();
	virtual void Render(Camera *camera);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetUseEnergy() { return useEnergy; }
	int GetDamage() { return damage; }
	void SetDamage(int damage) { this->damage = damage; }
};

