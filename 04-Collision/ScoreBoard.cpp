#include "ScoreBoard.h"
#include "Enemy.h"


ScoreBoard::ScoreBoard(Simon *simon, int bossHP, LPDIRECT3DDEVICE9 d3ddv, LPD3DXSPRITE spriteHandler)
{
	this->bossHP = bossHP;
	this->simon = simon;
	this->d3ddv = d3ddv;
	this->spriteHandler = spriteHandler;
	startkeyobject = new StartKeyObject(SCREEN_WIDTH, 80);
	startkeyobject->SetPosition(0, 0);

	simonHPList = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* simonHP = new HP(1);
		simonHP->SetPosition(120 + 12 * (i + 1), 40);
		simonHPList->push_back(simonHP);
	}
	enemyHPList = new std::vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* enemyHP = new HP(3);
		enemyHP->SetPosition(120 + 12 * (i + 1), 60);
		enemyHPList->push_back(enemyHP);
	}
	noHPList = new vector<HP*>();
	for (int i = 0; i < 16; i++)
	{
		HP* noHP = new HP(2);
		noHP->SetPosition(120 + 12 * (i + 1), 40);
		noHPList->push_back(noHP);
	}

	heart = new Item(ITEM_SMALL_HEART);
	heart->SetPosition(380, 43);

	axe = new Item(ITEM_AXE);
	axe->SetPosition(335, 45);

	holyWater = new Item(ITEM_HOLY_WATER);
	holyWater->SetPosition(335, 45);

	boomerang = new Item(ITEM_BOOMERANG);
	boomerang->SetPosition(335, 45);

	dagger = new Item(ITEM_DAGGER);
	dagger->SetPosition(335, 50);

	stopWatch = new Item(ITEM_STOP_WATCH);
	stopWatch->SetPosition(335, 45);

	upgrade1 = new Item(ITEM_UPGRADE_1);
	upgrade1->SetPosition(450, 45);

	upgrade2 = new Item(ITEM_UPGRADE_2);
	upgrade2->SetPosition(450, 45);

	font = NULL;

	D3DXFONT_DESC FontDesc = {
		20,
		13,
		10,
		10,
		false,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLEARTYPE_QUALITY,
		FF_DONTCARE, L"font\\prstart.ttf" };

	
	D3DXCreateFontIndirect(d3ddv, &FontDesc, &font);

	SetRect(&rect, 0, 20, SCREEN_WIDTH, 85);
	information = L"SCORE_000000 TIME 0000 STAGE 00\n";
	information += L"PLAYER                                         -5\n";
	information += L"ENEMY                                         P-3\n";
}


ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update(int bossHP, int time, int life, int stage)
{

	this->time = time;
	this->stage = stage;
	this->bossHP = bossHP;

	wstring scoreString = to_wstring(simon->GetScore());
	while (scoreString.length() < 6)
		scoreString = L"0" + scoreString;


	wstring timeString = to_wstring(this->time);
	while (timeString.length() < 4)
		timeString = L"0" + timeString;


	wstring stageString = to_wstring(this->stage);
	while (stageString.length() < 2)
		stageString = L"0" + stageString;


	information = L"SCORE_" + scoreString + L" TIME " + timeString + L" STAGE " + stageString + L"\n";
	information += L"PLAYER                                    -" + to_wstring(simon->GetEnergy()) + L"\n";
	information += L"ENEMY                                   P-" + to_wstring(simon->GetLife()) + L"\n";


	switch (simon->GetTypeOfWeapon())
	{
	case ITEM_AXE:
		weapon = nullptr;
		weapon = axe;
		break;
	case ITEM_HOLY_WATER:
		weapon = nullptr;
		weapon = holyWater;
		break;
	case ITEM_BOOMERANG:
		weapon = nullptr;
		weapon = boomerang;
		break;
	case ITEM_DAGGER:
		weapon = nullptr;
		weapon = dagger;
		break;
	case ITEM_STOP_WATCH:
		weapon = nullptr;
		weapon = stopWatch;
		break;
	default:
		break;
	}
}

void ScoreBoard::Render(Camera *camera)
{
	RECT newRect;
	startkeyobject->Render();
	SetRect(&newRect, 0, 0, SCREEN_WIDTH, 200);
		font->DrawText(spriteHandler, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255,255));
	
	for (int i = 0; i < noHPList->size(); i++)
	{
		noHPList->at(i)->Render();
	}
	int count = 0;
	for (int i = 0; i < simonHPList->size(); i++)
	{
		if (count < simon->GetHP())
		{
			simonHPList->at(i)->Render();
		}
		count++;
	}
	count = 0;
		for(int i=0;i<enemyHPList->size();i++)
		{
		if (count < bossHP)
		{
			enemyHPList->at(i)->Render();
		}
		count++;
	}
	heart->Render();
	if(weapon!=nullptr)
		weapon->Render();
	switch (simon->GetNumberOfWeapon()) {
	case 2: upgrade1->Render(); break;
	case 3: upgrade2->Render(); break;
	}
}
