#include "StateOutCastle.h"
#include "StateManager.h"


StateOutCastle::StateOutCastle()
{
	camera = new Camera(0, -112);
	CSprites * sprites = CSprites::GetInstance();
	tilemap = new TileMap(1504.0f, 288.0f, sprites->Get(0), 32.0f, 32.0f);
	tilemap->LoadListTileFromFile("mapread\\stateoutcastle.txt");
	scoreboard = new ScoreBoard(simon, 16, StateManager::d3ddv, StateManager::spriteHandler);
	time = 0;
	leftmap = new MapCollision(2, SCREEN_HEIGHT);
	leftmap->SetPosition(0, -47);
	listObject.push_back(leftmap);
	rightmap = new MapCollision(0, SCREEN_HEIGHT);
	rightmap->SetPosition(1520, -47);
	listObject.push_back(rightmap);
	lr = new LoadResources();
	lr->Load("loadresourcesfromfile\\object_stateoutcastle.txt",&listObject);
	transparentobject = new TransparentObject(32,32);
	transparentobject->SetPosition(1430, 270);
	coObjects.push_back(transparentobject);
	transparentobject1 = new TransparentObject(0,15);
	transparentobject1->SetPosition(1380, 270);
	coObjects.push_back(transparentobject1);
	simon->SetPosition(2, 210);
	simon->nx = 1;
	simon->SetControlKey(true);
	Item::TakeSimonPointer(simon);
	for (int i = 0; i < listObject.size(); i++)
		coObjects.push_back(listObject[i]);
	castle = new Castle();
	castle->SetPosition(1408, 0);
	castle->SetEnable(false);
	grid = new Grid(1536,320,256,160);
	grid->Add(&coObjects);

}

void StateOutCastle::Render(Camera *camera)
{
	camera = this->camera;
	tilemap->Render(camera);
	scoreboard->Render(camera);
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->isEnable == true)
			listItem[i]->Render(camera);
	}
	transparentobject->Render(camera);
	transparentobject1->Render(camera);
	for (int i = 0; i < listObject.size(); i++)
		listObject[i]->Render(camera);

	simon->Render(camera);
	castle->Render(camera);
}

void StateOutCastle::Update(DWORD dt)
{
	if (Enemy::IsStop != true)
	{
		time += dt;
		scoreboard->Update(16, 1000 - time * 0.001, 3, 1);
	}
	if (Enemy::IsStop == true) {

		if (GetTickCount() - Enemy::timestop_start > 5000)
		{
			Enemy::IsStop = false;
			Enemy::timestop = 0;
			Enemy::timestop_start = 0;
		}

	}
	grid->GetListOfObjects(&coObjects, camera);
	simon->Update(dt, &coObjects);
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);
		if (listObject[i]->IsDead())
		{
			Item *item = new Item();
			item->SetPosition(listObject[i]->x, listObject[i]->y);
			listItem.push_back(item);
			listObject[i]->SetDead(false);
			coObjects.clear();
			coObjects.push_back(item);
			grid->Add(&coObjects);
		}

	}
	for (int i = 0; i < listItem.size(); i++)
		listItem[i]->Update(dt,&coObjects);
	if (transparentobject->isDead==true)
	{
		Item *item = new Item(ITEM_MONEY);
		item->SetPosition(1250, 290);
		item->SetState(ITEM_STATE_UP);
		listItem.push_back(item);
		coObjects.clear();
		coObjects.push_back(item);
		grid->Add(&coObjects);
		transparentobject->isDead = false;
	}
	if (transparentobject1->isDead == true)
	{
		castle->SetEnable(true);
		simon->SetState(SIMON_STATE_WALKING_CASTLE);
		simon->nx = 1;
		if (transparentobject->isEnable == true)
			transparentobject->isEnable = false;
		timeDelay += dt;
		if (timeDelay >= STATE_OUTCASTLE_LIVE_TIME)
		{
			SetChangingState(true);
		}
	}
	transparentobject->Update(dt);
	transparentobject1->Update(dt);
	if (this->simon->x >= SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH/2 && this->simon->x <= 1536 - SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH/2)
	{

		D3DXVECTOR3 currentCamera = camera->GetCameraPosition();
		currentCamera.x = this->simon->x - SCREEN_WIDTH / 2 + SIMON_BBOX_WIDTH / 2;
		camera->SetCameraPosition(currentCamera.x, currentCamera.y);
	}
	
}


bool StateOutCastle::GetChangingState()
{
	return GameState::GetChangingState();
}

void StateOutCastle::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void StateOutCastle::DestroyAll()
{
	delete(tilemap);
	for (int i = 0; i < coObjects.size(); i++)
		delete(coObjects[i]);
	for(int i=0;i<listObject.size();i++)
	delete(listObject[i]);
	delete(camera);
}

StateOutCastle::~StateOutCastle()
{
}





