#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "Brick.h"
#include "Torch.h"
#include "MapCollision.h"
#include "TransparentObject.h"
#include "Castle.h"
#include "ScoreBoard.h"
#include "Grid.h"
#include "Cell.h"
#define STATE_OUTCASTLE_LIVE_TIME 2000

class StateOutCastle : public GameState
{
private:
	TileMap *tilemap;
	TransparentObject *transparentobject;
	TransparentObject *transparentobject1;
	MapCollision *leftmap;
	MapCollision *rightmap;
	Castle *castle;
	ScoreBoard *scoreboard;
	Grid *grid;
public:
	StateOutCastle();
	~StateOutCastle();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
};

