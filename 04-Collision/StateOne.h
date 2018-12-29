#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Brick.h"
#include "MapCollision.h"
#include "Candle.h"
#include "ScoreBoard.h"
#include "Stair.h"
#include "StairCheckObject.h"
#include "Zombie.h"
#include "BlackLeopard.h"
#include "Wall.h"
#include "Door.h"
#include "TransparentObject.h"
#include "VampireBat.h"
#include "FishMan.h"
#include "PhantomBat.h"
#include "WaterEffects.h"
class StateOne:public GameState
{
	TileMap *tilemap;
	MapCollision *leftmap;
	MapCollision *rightmap;
	ScoreBoard *scoreboard;
	Zombie *zombie[3];
	BlackLeopard *blackleopard[3];
	Door *door;
	Door *door1;
	Door *door2;
	TransparentObject *transparentobject;
	TransparentObject *transparentobject1;
	VampireBat *vampirebat;
	FishMan *fishman[2];
	PhantomBat *phantombat;
	WaterEffects *watereffects[3];
public:
	StateOne();
	~StateOne();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void UpdateZombie(DWORD dt);
	void UpdateBlackLeopard(DWORD dt);
	void UpdateVampireBat(DWORD dt);
	void UpdateFishMan(DWORD dt);
	bool IsInCamera(float x, float y);
	void UpdateWaterEffect(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
};

