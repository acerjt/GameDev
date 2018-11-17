#pragma once
#include "GameObject.h"
#include "Simon.h"
#include <time.h>


#define ITEM_SMALL_HEART	9001
#define ITEM_BIG_HEART		9002
#define ITEM_ROAST			9003
#define ITEM_MORNINGSTAR	9004
#define ITEM_AXE			9005
#define ITEM_CROSS			9006
#define ITEM_HOLY_WATER		9007
#define ITEM_KNIFE			9008
#define ITEM_TIME_STOP		9009
#define ITEM_INVISIBLE		9010
#define ITEM_MONEY			9011
#define ITEM_BALL			9012
#define ITEM_UPGRADE_1		9013
#define ITEM_UPGRADE_2		9014
#define ITEM_ROSARY			9015


#define ID_TEX_ITEM_BALL			1
#define ID_TEX_ITEM_SMALL_HEART		2
#define ID_TEX_ITEM_BIG_HEART		3
#define ID_TEX_ITEM_ROAST			4
#define ID_TEX_ITEM_WHIP			5
#define ID_TEX_ITEM_AXE				6
#define ID_TEX_ITEM_CROSS			7
#define ID_TEX_ITEM_HOLY_WATER		8
#define ID_TEX_ITEM_KNIFE			9
#define ID_TEX_ITEM_TIME_STOP		10
#define ID_TEX_ITEM_INVISIBLE		11
#define ID_TEX_ITEM_MONEY			12
#define ID_TEX_ITEM_UPGRADE_1		13
#define ID_TEX_ITEM_UPGRADE_2		14
#define ID_TEX_ITEM_ROSARY			15



class Item;
typedef Item * LPITEM;

class Item:public CGameObject
{

//protected:
//	bool changedState;
//	std::string itemPath;
	
	static Simon *simon;
	CSprite *sprite;
//	float remainTime; // Time to disapear after being initialized
//	static std::vector<CGameObject*> *listEnemy;
	int width;
	int height;
//	float stateClearTime;
public:
	int itemType;
	static bool isKillAll;
public:
	Item();
	
	~Item();
	static void TakeSimonPointer(Simon *simon);
	void Render(Camera *camera);
	void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void Random();
	void RandomItem();
	void RandomSubWeapon();
	void UpgradeMorningstar();

	//void AddEnergy(int energy); // SMALL_HEART || BIG_HEART : Add energy to Simon
	//void RecoverHP(int hp); // ROAST : Simon's HP after healed
	//void UpgradeWhip(); // WHIP : Upgrade whip for Simon
	//void ChangeSubWeapon(); // ALL SUB WEAPON : Change sub weapon after take item, USE TAG
	//void MakeInvincible(int time); // INVISIBLE : Make simon invincible to enemy
	//void AddScore(int point); // MONEY : Add more point to score
	//void KillAll(); // ROSARY : Kill all enemy in camera
	//void IncreaseSubWeapon(int no); // DOUBLE/TRIPPLE SHOT : Increase number of subweapon use onscreen
	//void NextStage(float gameTime); // BALL : Heal Simon and change stage
	//void StopTime(float time);

	static bool IsKillAll() { return isKillAll; }
	static void SetIsKillAll(bool _isKillAll) { isKillAll = _isKillAll; }

};

