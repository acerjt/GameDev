#pragma once
#include "GameState.h"
#include "Scenes.h"
#include "BatIntro.h"
#include "Helicopter.h"
#include "Brick.h"

#define STATE_INTRO_LIVE_TIME	3000
class StateIntro:public GameState
{
private:
	DWORD timeDelay;
	Scenes *scene;
	CBrick *brick;
	BatIntro *batintro[2];
	Helicopter *helicopter;

	//Ground *ground;


//	void InitAnim();


public:
	StateIntro();
	~StateIntro();

	void Render(Camera *camera);
	void Update(DWORD dt);

	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(DWORD dt) { return true; }
	void DestroyAll();

};

