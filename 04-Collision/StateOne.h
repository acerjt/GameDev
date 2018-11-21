#pragma once
#include "GameState.h"
#include "TileMap.h"
class StateOne:public GameState
{
	TileMap *tilemap;
public:
	StateOne();
	~StateOne();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(DWORD dt) { return true; }
};

