#pragma once
#include "GameState.h"
#include "TileMap.h"
#include "Simon.h"
#include "Brick.h"
#include "Torch.h"
#include "Zombie.h"
//#include "UI.h"
#include "Item.h"
//#include "WaterAnimation.h"
class StateOutCastle : public GameState
{
private:
	//Simon *simon;
	TileMap *tilemap;
	Torch *torch[6];


	CBrick *brick;
	CGameObject *cameraObject;
	CGameObject *leftCamera;
	CGameObject *rightCamera;


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

