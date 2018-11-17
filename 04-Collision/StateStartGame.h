#pragma once
#include "Batstartgame.h"
#include "Scenes.h"
#include "GameState.h"

class StateStartGame :public GameState
{
	Scenes *scene;
	Batstartgame *bat_st;
public:
	StateStartGame();
	~StateStartGame();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(DWORD dt) { return true; }
};



