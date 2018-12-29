#pragma once
#include "GameObject.h"
#include "Simon.h"
#include <time.h>


#define ITEM_BALL			9001
#define ITEM_MONEY			9002
#define ITEM_SMALL_HEART	9003	
#define ITEM_BIG_HEART		9004
#define ITEM_ROAST			9005
#define ITEM_MORNINGSTAR	9006
#define ITEM_AXE			9007
#define ITEM_BOOMERANG		9008
#define ITEM_HOLY_WATER		9009
#define ITEM_DAGGER			9010
#define ITEM_STOP_WATCH		9011
#define ITEM_INVISIBLE		9012
#define ITEM_UPGRADE_1		9013
#define ITEM_UPGRADE_2		9014
#define ITEM_CROSS			9015
#define ITEM_MONEY_WHITE	9016
#define ITEM_MONEY_RED		9017
#define ITEM_MONEY_PURPLE	9018
							
								
#define ITEM_STATE_UP				9000
#define ITEM_STATE_IDLE				9001

class Item;
typedef Item * LPITEM;

class Item:public CGameObject
{
	static Simon *simon;
	CSprite *sprite;
	int itemType;
	CAnimation *anirender;
public:
	Item();
	Item(int itemType);
	~Item();
	void SetState(int state);
	static void TakeSimonPointer(Simon *simon);
	void Render(Camera *camera);
	int GetCurrentFrame();
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Random();
	void RandomItem();
	void RandomWeapon();
	int GetItemType() { return itemType; }
};

