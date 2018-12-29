#pragma once
#include "Batstartgame.h"
#include "Scenes.h"
#include "GameState.h"
#include "StartKeyObject.h"

#define STATE_START_GAME_LIVE_TIME 3000

class StateStartGame :public GameState
{
	StartKeyObject *startkeyobject;
	Scenes *scene;
	Batstartgame *batstartgame;
	DWORD timeDelay;
public:
	static bool isPress;
public:
	StateStartGame();
	~StateStartGame();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
};



