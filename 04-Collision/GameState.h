#pragma once
#include "Camera.h"
#include <fstream>
#include <vector>
#include "Game.h"
#include "debug.h"
#include "Item.h"
#include "Simon.h"
#include "Enemy.h"
#include "LoadResources.h"
static int score;
class GameState
{
protected:
	bool InBoss;
	Camera *camera;
	vector<LPGAMEOBJECT> listObject; 
	vector<LPGAMEOBJECT> coObjects;
	vector<LPGAMEOBJECT> listObject1;
	vector<LPENEMY> listEnemy;
	vector<LPITEM> listItem;
	DWORD time;
	DWORD timeDelay;
	D3DXVECTOR3 simonCheckpoint; 
	D3DXVECTOR3 cameraCheckpoint; 
	LoadResources *lr;
	DWORD timeKillAll;
	bool choose;
public:
	static Simon* simon;
	int state;
	static bool changeState;
public:
	
	GameState() {};
	~GameState() {};
	virtual void Render(Camera *camera) {};
	virtual void Update(DWORD dt);
	virtual void DestroyAll() = 0;
	virtual bool GetChangingState() { return changeState; };
	virtual void SetChangingState(bool status) { changeState = status; }
};








