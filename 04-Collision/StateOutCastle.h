#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "Brick.h"
#include "Torch.h"
#include "MapCollision.h"
#include "TransparentObject.h"
#include "Castle.h"
#define STATE_OUTCASTLE_LIVE_TIME 2000

class StateOutCastle : public GameState
{
	DWORD timeDelay;
private:
	TileMap *tilemap;
	Torch *torch[6];
	TransparentObject *transparentobject;
	TransparentObject *transparentobject1;
	CBrick *brick;
	MapCollision *leftmap;
	MapCollision *rightmap;
	Castle *castle;

	//UI *ui;
	

public:
	StateOutCastle();
	~StateOutCastle();
	void Render(Camera *camera);
	void Update(DWORD dt);
	void DestroyAll();
	bool GetChangingState();
	void SetChangingState(bool status);
	bool CameraFollowHandle(DWORD dt) { return true; }


};

