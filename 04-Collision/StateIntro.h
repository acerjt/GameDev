#pragma once
#include "GameState.h"
#include "Scenes.h"
#include "BatIntro.h"
#include "Helicopter.h"
#include "Brick.h"
#include "ScoreBoard.h"

#define STATE_INTRO_LIVE_TIME	3000
class StateIntro:public GameState
{
private:
	DWORD timeDelay;
	Scenes *scene;
	CBrick *brick;
	BatIntro *batintro[2];
	Helicopter *helicopter;
	ScoreBoard *scoreboard;
public:
	StateIntro();
	~StateIntro();
	void Render(Camera *camera);
	void Update(DWORD dt);
	bool GetChangingState();
	void SetChangingState(bool status);
	void DestroyAll();

};

