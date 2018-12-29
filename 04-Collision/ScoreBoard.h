#pragma once
#include "Camera.h"
#include <string>
#include "Item.h"
#include <vector>
#include "Simon.h"
#include "HP.h"
#include "StartKeyObject.h"
class ScoreBoard
{
	
private:
	ID3DXFont *font;
	RECT rect;
	Simon *simon;
	LPDIRECT3DDEVICE9 d3ddv;
	StartKeyObject *startkeyobject;
	wstring information;
	vector<HP*> *simonHPList;
	vector<HP*> *enemyHPList;
	vector<HP*> *noHPList;
	CSprite *sprite;
	LPD3DXSPRITE spriteHandler;
	Item* heart;
	Item* weapon;
	Item* axe;
	Item* holyWater;
	Item* boomerang;
	Item* dagger;
	Item* stopWatch;
	Item* upgrade1;
	Item* upgrade2;
	int bossHP;
	int score;
	int time;
	int item;
	int energy;
	int life;
	int stage;
public:
	ScoreBoard(Simon *simon, int bossHP, LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE spriteHandler);
	~ScoreBoard();
	void Update(int bossHP, int time, int life, int stage);
	void Render(Camera *camera);
};

