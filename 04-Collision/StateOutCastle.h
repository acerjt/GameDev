#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "Brick.h"
#include "Torch.h"
#include "MapCollision.h"
#include "TransparentObject.h"
class StateOutCastle : public GameState
{
private:
	TileMap *tilemap;
	Torch *torch[6];
	TransparentObject *transparentobject;
	CBrick *brick;
	MapCollision *leftmap;
	MapCollision *rightmap;


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

