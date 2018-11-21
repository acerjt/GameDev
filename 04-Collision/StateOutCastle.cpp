#include "StateOutCastle.h"



StateOutCastle::StateOutCastle()
{

	camera = new Camera(0, -85);
	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	textures->Add(ID_TEX_MAP_OUT_CASTLE, L"textures\\tilesetoutcastle.png", D3DCOLOR_XRGB(255, 0, 255));
	sprites->Add(0, 0, 0, 319, 159, textures->Get(ID_TEX_MAP_OUT_CASTLE));

	tilemap = new TileMap(1506.0f, 288.0f, sprites->Get(0), 32.0f, 32.0f);
	tilemap->LoadListTileFromFile("mapread\\stateoutcastle.txt");

	leftmap = new MapCollision(2, SCREEN_HEIGHT);
	leftmap->SetPosition(0, -47);
	listObject.push_back(leftmap);
	rightmap = new MapCollision(0, SCREEN_HEIGHT);
	rightmap->SetPosition(1520, -47);
	listObject.push_back(rightmap);
	brick = new CBrick(1536, BRICK_BBOX_HEIGHT, STATE_OUT_CASTLE);
	brick->SetPosition(0, 289);
	listObject.push_back(brick);
	torch[0] = new Torch();
	torch[0]->SetPosition(176, 225);
	torch[1] = new Torch();
	torch[1]->SetPosition(432, 225);
	torch[2] = new Torch();
	torch[2]->SetPosition(686, 225);
	torch[3] = new Torch();
	torch[3]->SetPosition(942, 225);
	torch[4] = new Torch();
	torch[4]->SetPosition(1200, 225);
	for (int i = 0; i < 5; i++)
		listObject.push_back(torch[i]);
	transparentobject = new TransparentObject(32,32);
	transparentobject->SetPosition(1430, 270);
	coObjects.push_back(transparentobject);
	transparentobject1 = new TransparentObject(0,15);
	transparentobject1->SetPosition(1380, 270);
	coObjects.push_back(transparentobject1);
	simon->SetPosition(2, 210);
	simon->nx = 1;
	simon->IsControlKey = true;
	Item::TakeSimonPointer(simon);
	for (int i = 0; i < listObject.size(); i++)
		coObjects.push_back(listObject[i]);
	castle = new Castle();
	castle->SetPosition(1408, 0);
	castle->isEnable = false;

}

void StateOutCastle::Render(Camera *camera)
{
	camera = this->camera;
	tilemap->Render(camera);
	
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
	simon->Update(dt, &coObjects);
	
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);
		if (listObject[i]->isDead==true)
		{
			Item *item = new Item();
			item->SetPosition(listObject[i]->x, listObject[i]->y);
			listItem.push_back(item);
			listObject.erase(listObject.begin() + i);
			coObjects.push_back(item);	
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
		coObjects.push_back(item);
		transparentobject->isDead = false;
	}
	if (transparentobject1->isDead == true)
	{
		castle->isEnable = true;
		simon->SetState(SIMON_STATE_WALKING_CASTLE);
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
		currentCamera.x = this->simon->x - SCREEN_WIDTH / 2 + 33;
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
	//delete(simon);
	delete(tilemap);
	delete(brick);
	for(int i=0;i<listObject.size();i++)
	delete(listObject[i]);
	delete(camera);
}

StateOutCastle::~StateOutCastle()
{
}





