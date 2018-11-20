#pragma once
#include "StateStartGame.h"
#include "StateIntro.h"
#include "StateOutCastle.h"
class StateManager
{
private:
	GameState* gameState;
public:
	int stateID;
public:
	StateManager();
	~StateManager();
	void LoadState(int stateID,Simon *simon);
	void NextStateLevel();
	void Render(Camera *camera);
	void Update(DWORD dt);
};

