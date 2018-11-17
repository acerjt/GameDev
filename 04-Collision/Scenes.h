#pragma once
#include "GameObject.h"


#define SCENE_STATE_START 0
#define SCENE_STATE_INTRO 1
#define SCENE_STATE_OUT_CASTLE 2
#define SCENE_STATE_1	  3
#define SCENE_STATE_2     4

#define SCENE_LIVE_TIME 7000

#define SCENE_BBOX_WIDTH  0
#define SCENE_BBOX_HEIGHT 0
class Scenes : public CGameObject
{
	
public: 
	float timeDelay=0;
	static int changescene;
public:
	virtual void Update(DWORD dt);
	virtual void Render(Camera *camera);
	virtual void Render();
	//void SetTimeLive(int timelive);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	//virtual void Render(Camera *camera);
	//void StartUntouchable() { press_start = GetTickCount(); }
	//void SetState(int state);
	Scenes();
	~Scenes();
};

