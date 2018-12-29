#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Textures.h"
#include "ColliderEffect.h"
#include "DeadEffect.h"
using namespace std;

		// special texture to draw object bounding box

class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x; 
	float y;
	
	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;
	int width;
	int height;
	int nx;	 
	int type;
	int state;
	int id;
	DWORD dt; 
	Camera *camera;
	vector<LPANIMATION> animations;
	ColliderEffect *collider;
	DeadEffect *deadeffect;
	bool isEnable;
	bool isDead;
public: 
	void SetPosition(float x, float y) { this->x = x, this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	D3DXVECTOR3 GetPosition() { return D3DXVECTOR3(x, y,0); }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }

	int GetState() { return this->state; }
	void SetEnable(bool enable);
	bool IsEnable() { return isEnable; }

	void SetDead(bool _isDead) { isDead = _isDead; }
	bool IsDead() { return isDead; }
	void RenderBoundingBox(Camera* camera);

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(int aniId);
	void resetAni(int aniID) { animations[aniID]->reset(); }
	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render(Camera *camera);
	virtual void SetState(int state) { this->state = state; }
	void SetId(int id) { this->id = id; }
	int GetId() { return id; }
	void SetWidth(int width) { this->width = width; }
	void SetHeight(int height) { this->height = height; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	void SetType(int type) { this->type = type; }
	int GetType() { return type; }
	ColliderEffect *GetColliderEffect() { return collider; }
	DeadEffect *GetDeadEffect() { return deadeffect; }
	~CGameObject();
};

