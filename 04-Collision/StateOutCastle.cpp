#include "StateOutCastle.h"



StateOutCastle::StateOutCastle()
{

	camera = new Camera(0, 0);

	CTextures * textures = CTextures::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;
	textures->Add(ID_TEX_MAP_OUT_CASTLE, L"textures\\background_out_castle.png", D3DCOLOR_XRGB(255, 0, 255));
	LPDIRECT3DTEXTURE9 tex_map_outcastle = textures->Get(ID_TEX_MAP_OUT_CASTLE);
	sprites->Add(0, 0, 0, 639, 255, tex_map_outcastle);

	tilemap = new TileMap(1536.0f, 392.0f, sprites->Get(0), 64.0f, 64.0f);
	tilemap->LoadListTileFromFile("mapread\\lv1.txt");

	brick = new CBrick(1536, BRICK_BBOX_HEIGHT, STATE_OUT_CASTLE);
	brick->SetPosition(0, 400);
	torch[0] = new Torch();
	torch[0]->SetPosition(176, 336);
	torch[1] = new Torch();
	torch[1]->SetPosition(432, 336);
	torch[2] = new Torch();
	torch[2]->SetPosition(686, 336);
	torch[3] = new Torch();
	torch[3]->SetPosition(942, 336);
	torch[4] = new Torch();
	torch[4]->SetPosition(1200, 336);	
	for (int i = 0; i < 5; i++)
	{
		listObject.push_back(torch[i]);
	}
	listObject.push_back(brick);

	simon = new Simon();


	simon->SetPosition(2, 320);
	Item::TakeSimonPointer(simon);
	for (int i = 0; i < listObject.size(); i++)
	{
		coObjects.push_back(listObject[i]);
	}

	
	//listObject.push_back(simon);
	//simon->SetPosition(20, 0);
	/*castleSprite = new Sprite(1408, 347);
	if (!castleSprite->Initialize(gDevice, CASTLE_SPRITE))
		return false;

	tileMap = new TileMap(1536, 392, sprite, 64, 64);
	tileMap->LoadListTileFromFile(LEVEL_ONE_MATRIX_BG);

	cameraObject = new GameObject();
	cameraObject->Initialize(gDevice, SIMON_SPRITE, viewPort->GetCameraPosition().x, viewPort->GetCameraPosition().y, 5);

	leftCamera = new Ground(2, 450);
	leftCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\1.png", viewPort->GetCameraPosition().x - 2, viewPort->GetCameraPosition().y, TAG_GROUND);

	rightCamera = new Ground(2, 450);
	rightCamera->Initialize(gDevice, "Resource\\sprites\\Ground\\1.png", viewPort->GetCameraPosition().x + GAME_WIDTH, viewPort->GetCameraPosition().y, TAG_GROUND);

	quadTree = new QuadTree(gDevice, viewPort);
	quadTree->Load("Resource\\sprites\\QuadTree\\lv1.txt");

	list = new std::vector<GameObject*>();

	simon->SetPosition(100, 150);
	simon->Reload();

	changeState = false;

	Sound::GetInstance()->Stop(GAME_START_PROLOGUE);

	if (!Sound::GetInstance()->IsPLaying(STAGE_01_VAMPIRE_KILLER))
		Sound::GetInstance()->PlayLoop(STAGE_01_VAMPIRE_KILLER);

	Item::TakeSimonPointer(simon);

	listItem = new std::vector<Item*>();

	ui = new UI();
	ui->Initialize(gDevice, simon, 16);
	time = 0;

	return true;*/
}

void StateOutCastle::Render(Camera *camera)
{
	camera = this->camera;
	tilemap->Render(camera);


	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Render(camera);
	}
	for (int i = 0; i < listItem.size(); i++)
	{
		if(listItem[i]->isEnable==true)
			listItem[i]->Render(camera);
	}
	simon->Render(camera);
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
	{
		listItem[i]->Update(dt,&coObjects);
	}


	
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
	delete(cameraObject);
	for(int i=0;i<listObject.size();i++)
	delete(listObject[i]);
	delete(camera);
}

StateOutCastle::~StateOutCastle()
{
}





