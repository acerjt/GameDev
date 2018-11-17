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
	static Simon *simon;
public:
	StateManager();
	~StateManager();
	//bool Initialize(HWND hwnd);
	void LoadState(int stateID,Simon *simon);
	void NextStateLevel();
	void Render(Camera *camera);
	void Update(DWORD dt);
};

