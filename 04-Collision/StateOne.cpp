#include "StateOne.h"
#include "StateManager.h"


StateOne::StateOne()
{

	camera = new Camera(0, -80);
	CSprites * sprites = CSprites::GetInstance();

	tilemap = new TileMap(5632.0f, 704.0f, sprites->Get(1), 32.0f, 32.0f);
	tilemap->LoadListTileFromFile("mapread\\stateone.txt");
	
	leftmap = new MapCollision(2, SCREEN_HEIGHT);
	leftmap->SetPosition(0, -47);
	coObjects.push_back(leftmap);
	rightmap = new MapCollision(0, SCREEN_HEIGHT);
	rightmap->SetPosition(5632, -47);
	coObjects.push_back(rightmap);

	simon->SetPosition(200, 253);
	simon->SetControlKey(true);
	lr = new LoadResources();
	lr->Load("loadresourcesfromfile\\object_stateone.txt", &listObject);
	for (int i = 0; i < listObject.size(); i++)
		coObjects.push_back(listObject[i]);
#pragma region Ground
	
	door = new Door();
	door->SetPosition(3056, 32);
	door->SetType(OBJECT_DOOR);
	coObjects.push_back(door);
	listObject.push_back(door);

	door1 = new Door();
	door1->SetPosition(4080, 32);
	door1->SetType(OBJECT_DOOR);
	coObjects.push_back(door1);
	listObject.push_back(door1);

	door2 = new Door();
	door2->SetPosition(5616, 96);
	door2->SetType(OBJECT_DOOR_1);
	coObjects.push_back(door2);
	listObject.push_back(door2);

	transparentobject = new TransparentObject(10, 10);
	transparentobject->SetPosition(3200, 64);
	transparentobject->SetEnable(true);
	coObjects.push_back(transparentobject);
	listObject1.push_back(transparentobject);

	transparentobject1 = new TransparentObject(10, 10);
	transparentobject1->SetPosition(3950, 580);
	coObjects.push_back(transparentobject1);
	listObject1.push_back(transparentobject1);

#pragma endregion
#pragma region Enemy



	for (int i = 0; i < 3; i++)
	{
		zombie[i] = new Zombie();
		zombie[i]->SetPosition(SCREEN_WIDTH + (i + 1) * 50, 200);
		zombie[i]->SetEnable(true);
		zombie[i]->SetState(ZOMBIE_STATE_WALKING_LEFT);
		coObjects.push_back(zombie[i]);
		listEnemy.push_back(zombie[i]);

	}
	for (int i = 0; i < 3; i++)
	{
		blackleopard[i] = new BlackLeopard();
		blackleopard[i]->SetEnable(true);
		blackleopard[i]->SetState(BLACK_LEOPARD_STATE_IDLE);
		blackleopard[i]->SetIsGroundNexTFrame(true);
		coObjects.push_back(blackleopard[i]);
		listEnemy.push_back(blackleopard[i]);
	}
	blackleopard[0]->SetPosition(1380, 0);
	blackleopard[1]->SetPosition(1764, 0);
	blackleopard[2]->SetPosition(1900, 0);

	
	vampirebat = new VampireBat();
	vampirebat->SetPosition(3800, 100);
	vampirebat->SetEnable(false);
	coObjects.push_back(vampirebat);
	listEnemy.push_back(vampirebat);

	for (int i = 0; i < 2; i++)
	{
		fishman[i] = new FishMan();
		fishman[i]->SetPosition(3200 + i * rand() % 200, 280);
		fishman[i]->SetEnable(true);
		fishman[i]->SetState(FISH_MAN_STATE_JUMP);
		coObjects.push_back(fishman[i]);
		listEnemy.push_back(fishman[i]);
		coObjects.push_back(fishman[i]->GetFireBall());
	}

	phantombat = new PhantomBat();
	phantombat->SetPosition(5350,0);
	phantombat->SetEnable(true);
	coObjects.push_back(phantombat);
#pragma endregion
	for (int i = 0; i < 3; i++)
	{
		watereffects[i] = new WaterEffects();
		watereffects[i]->SetEnable(false);
	}
	scoreboard = new ScoreBoard(simon, phantombat->GetHP(), StateManager::d3ddv, StateManager::spriteHandler);

}


StateOne::~StateOne()
{

}

void StateOne::Render(Camera * camera)
{
	camera = this->camera;
	tilemap->Render(camera);
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Render(camera);
	}
	for (int i = 0; i < listObject1.size(); i++)
	{
		listObject1[i]->Render(camera);
	}
	for (int i = 0; i < listItem.size(); i++)
	{
		if (listItem[i]->isEnable == true)
			listItem[i]->Render(camera);
	}
	for (int i = 0; i < listEnemy.size(); i++)
	{
		listEnemy[i]->Render(camera);
	}
	for (int i = 0; i < 3; i++)
		if (watereffects[i]->IsEnable())
			watereffects[i]->Render(camera);
	simon->Render(camera);
	phantombat->Render(camera);
	scoreboard->Render(camera);
}

void StateOne::Update(DWORD dt)
{
	GameState::Update(dt);
	if (Enemy::IsStop != true)
	{
		time += dt;
		scoreboard->Update(phantombat->GetHP(), 500 - time * 0.001, 3, 2);
	}
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);
		if (listObject[i]->isDead == true)
		{
			Item *item = new Item();
			item->SetPosition(listObject[i]->x, listObject[i]->y);
			listItem.push_back(item);
			listObject[i]->isDead = false;
			coObjects.push_back(item);
		}
	}
	if (InBoss == true)
	{
		if (phantombat->IsEnable() == true)
		{
			phantombat->CalculateSimonPos(simon, dt);
		}
		else if(phantombat->IsDead() == true)
			{
			timeDelay += dt;
			if (timeDelay > 3000)
			{
				Item *ball = new Item(ITEM_BALL);
				ball->SetPosition(camera->GetCameraPosition().x + SCREEN_WIDTH/2, camera->GetCameraPosition().y+SCREEN_HEIGHT/2);
				coObjects.push_back(ball);
				listItem.push_back(ball);
				phantombat->isDead = false;
			}
		}
		phantombat->Update(dt);

	}
	for (int i = 0; i < listItem.size(); i++)
		listItem[i]->Update(dt, &coObjects);
	if (transparentobject1->isDead == true)
	{
		Item *item = new Item(ITEM_MONEY);
		item->SetPosition(3730, 515);
		item->SetState(ITEM_STATE_UP);
		listItem.push_back(item);
		coObjects.push_back(item);
		transparentobject1->isDead = false;
	}
	UpdateZombie(dt);
	UpdateBlackLeopard(dt);
	UpdateVampireBat(dt);
	UpdateFishMan(dt);
	for (int i = 0; i < listEnemy.size(); i++)
		listEnemy[i]->Update(dt, &coObjects);
	UpdateWaterEffect(dt);
	simon->Update(dt, &coObjects);
	if (simon->IsColliderWithDoor() == true)
	{
		camera->SetCameraPosition(camera->GetCameraPosition().x + 0.1*dt, camera->GetCameraPosition().y);
		if (camera->GetCameraPosition().x >= 2832 && camera->GetCameraPosition().x <3000)
		{
			door->SetAnimation(1);
			camera->SetCameraPosition(camera->GetCameraPosition().x, camera->GetCameraPosition().y);
			simon->SetColliderWithDoor(false);
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
		else if (camera->GetCameraPosition().x >= 3800 && camera->GetCameraPosition().x < 4000)
		{
			door1->SetAnimation(1);
			camera->SetCameraPosition(camera->GetCameraPosition().x, camera->GetCameraPosition().y);
			simon->SetColliderWithDoor(false);
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}
	}
	if (!transparentobject->IsEnable())
	{
		simon->SetState(SIMON_STATE_IDLE);
		door->SetAnimation(3);
		door1->SetAnimation(3);
		camera->SetCameraPosition(camera->GetCameraPosition().x + 0.1*dt, camera->GetCameraPosition().y);
		if (camera->GetCameraPosition().x >= 3072 && camera->GetCameraPosition().x < 3100)
		{
			camera->SetCameraPosition(camera->GetCameraPosition().x, camera->GetCameraPosition().y);
			transparentobject->SetEnable(true);
			transparentobject->SetPosition(4200, 64);
			leftmap->SetPosition(3072, 0);

			simon->SetControlKey(true);
		}
		else if (camera->GetCameraPosition().x >= 4096 && camera->GetCameraPosition().x < 4200)
			{
				camera->SetCameraPosition(camera->GetCameraPosition().x, camera->GetCameraPosition().y);
				transparentobject->SetEnable(true);
				transparentobject->SetPosition(0, 0);
				leftmap->SetPosition(4100, 0);

				simon->SetControlKey(true);
			}
	}
	if (this->simon->GetPosition().x >= SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH / 2 && this->simon->GetPosition().x <= 3088 - SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH / 2)
	{

		D3DXVECTOR3 currentCamera = camera->GetCameraPosition();
		currentCamera.x = this->simon->GetPosition().x - SCREEN_WIDTH / 2 + SIMON_BBOX_WIDTH / 2;
		camera->SetCameraPosition(currentCamera.x, currentCamera.y);
	}
	else
		if (this->simon->GetPosition().x >= 3102 && this->simon->GetPosition().x <= 4112 - SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH / 2)
		{

			D3DXVECTOR3 currentCamera = camera->GetCameraPosition();
			if (simon->GetPosition().x >= 3102 - SIMON_BBOX_WIDTH + SCREEN_WIDTH / 2 && simon->GetPosition().x <= 4112 - SCREEN_WIDTH / 2)
				currentCamera.x = this->simon->GetPosition().x - SCREEN_WIDTH / 2 + SIMON_BBOX_WIDTH / 2;
			camera->SetCameraPosition(currentCamera.x, currentCamera.y);
		}
		else
			if (this->simon->GetPosition().x >= 4125 && this->simon->GetPosition().x <= 5648 - SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH / 2)
			{
				if(camera->GetCameraPosition().x>=5130)
				{
					camera->SetCameraPosition(camera->GetCameraPosition().x, camera->GetCameraPosition().y);
					InBoss = true;
					leftmap->SetPosition(5648 - SCREEN_WIDTH, leftmap->GetPosition().y);
				}
				else if (simon->GetPosition().x >= 4125 - SIMON_BBOX_WIDTH + SCREEN_WIDTH / 2 && simon->GetPosition().x <= 5648 - SCREEN_WIDTH / 2)
					{
						D3DXVECTOR3 currentCamera = camera->GetCameraPosition();
						currentCamera.x = this->simon->GetPosition().x - SCREEN_WIDTH / 2 + SIMON_BBOX_WIDTH / 2;
						camera->SetCameraPosition(currentCamera.x, currentCamera.y);
					}		
			}
	if (simon->GetPosition().y > 290)
	{
		camera->SetCameraPosition(camera->GetCameraPosition().x, 270);
		simon->SetPosition(simon->GetPosition().x, simon->GetPosition().y);
	}
	else
		camera->SetCameraPosition(camera->GetCameraPosition().x, -80);
}

void StateOne::UpdateZombie(DWORD dt)
{
	if ((simon->GetPosition().x > 0 && simon->GetPosition().x < 890)
		|| (simon->GetPosition().x > 2220 && simon->GetPosition().x < 2950)
		|| (simon->GetPosition().x > 4200 && simon->GetPosition().x < 4950))
	{
		for (int i = 0; i < 3; i++)
		{
			if (!zombie[i]->IsEnable() && zombie[i]->respawnTime > 1000)
			{
				if ((simon->GetPosition().x > 0 && simon->GetPosition().x < 514)
					|| (simon->GetPosition().x > 2220 && simon->GetPosition().x < 2700)
					|| (simon->GetPosition().x > 4125 && simon->GetPosition().x < 4870))
				{
					zombie[i]->SetPosition(camera->GetCameraPosition().x + SCREEN_WIDTH - 1, simon->GetPosition().y);
					zombie[i]->SetState(ZOMBIE_STATE_WALKING_LEFT);
				}
				else
				{
					zombie[i]->SetPosition(camera->GetCameraPosition().x + 1, simon->GetPosition().y);
					zombie[i]->SetState(ZOMBIE_STATE_WALKING_RIGHT);
				}
				zombie[i]->SetEnable(true);
				zombie[i]->Respawn();
				if (i == 0)
				{
					zombie[1]->respawnTime = 500;
					zombie[2]->respawnTime = 500;
				}
				if (i == 1)
					zombie[2]->respawnTime = 500;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (!IsInCamera(zombie[i]->GetPosition().x, zombie[i]->GetPosition().y))
			zombie[i]->SetEnable(false);
	}
}
void StateOne::UpdateBlackLeopard(DWORD dt)
{
	for (int i = 0; i < 3; i++)
	{
		if ((blackleopard[i]->GetPosition().x > 2600 && blackleopard[i]->GetPosition().x < 1100))// && blackleopard[i]->GetState()==BLACK_LEOPARD_STATE_IDLE)
		{
			blackleopard[i]->SetEnable(false);
		}
		if (camera->GetCameraPosition().x > 2600 || camera->GetCameraPosition().x < 740)
		{
			blackleopard[i]->SetEnable(true);
			blackleopard[i]->SetHP(1);
			blackleopard[i]->SetState(BLACK_LEOPARD_STATE_IDLE);
			if (i == 0)
				blackleopard[0]->SetPosition(1380, 0);
			else if (i == 1)
				blackleopard[1]->SetPosition(1764, 0);
			else
				blackleopard[2]->SetPosition(1900, 0);
		}
		if (blackleopard[i]->GetState() == BLACK_LEOPARD_STATE_IDLE)
			blackleopard[i]->nx = (-simon->nx);
		if ((abs(simon->GetPosition().x - blackleopard[i]->GetPosition().x) < 120) && blackleopard[i]->GetState() == BLACK_LEOPARD_STATE_IDLE)
		{
			if (blackleopard[i]->nx > 0)
				blackleopard[i]->SetState(BLACK_LEOPARD_STATE_WALKING_RIGHT);
			if (blackleopard[i]->nx < 0)
				blackleopard[i]->SetState(BLACK_LEOPARD_STATE_WALKING_LEFT);
		}
	}
}
void StateOne::UpdateVampireBat(DWORD dt)
{
	if (!IsInCamera(vampirebat->GetPosition().x, vampirebat->GetPosition().y))
		vampirebat->SetEnable(false);
	if (simon->GetPosition().x > 3201 && simon->GetPosition().x < 4000
		&& simon->GetPosition().y < 260)
	{
		if (!vampirebat->IsEnable() && vampirebat->respawnTime > 3000)
		{
			if (simon->GetPosition().x > 3201 && simon->GetPosition().x < 3300)
			{
				vampirebat->SetPosition(camera->GetCameraPosition().x + SCREEN_WIDTH - 1, simon->GetPosition().y);
				vampirebat->SetState(VAMPIRE_BAT_STATE_WALKING_LEFT);
				vampirebat->nx = -1;
			}
			else if (simon->GetPosition().x > 3300 && simon->GetPosition().x < 3600)
			{
				vampirebat->SetPosition(camera->GetCameraPosition().x + 1, simon->GetPosition().y);
				vampirebat->SetState(VAMPIRE_BAT_STATE_WALKING_RIGHT);
				vampirebat->nx = 1;
			}
			vampirebat->y = simon->GetPosition().y;
			vampirebat->Respawn();
		}
	}
}
void StateOne::UpdateFishMan(DWORD dt)
{
	for (int i = 0; i < 2; i++)
	{
		if (fishman[i]->GetPosition().y > 550 && fishman[i]->IsEnable())
		{
			watereffects[i]->SetEnable(fishman[i]->IsEnable());
			if (watereffects[i]->IsEnable())
			{
				watereffects[i]->SetVelocity();
				watereffects[i]->SetPosition(fishman[i]->GetPosition().x, fishman[i]->GetPosition().y + 30);
			}
			fishman[i]->SetEnable(false);
		}
		if (!IsInCamera(fishman[i]->GetPosition().x, fishman[i]->GetPosition().y))
			fishman[i]->SetEnable(false);
		if (!fishman[i]->IsEnable())
		{
			if (fishman[i]->respawnTime >= 4000
				&& (simon->GetPosition().x > 3088 && simon->GetPosition().x < 4096
					&& simon->GetPosition().y > 300 && simon->GetPosition().y < 530))
			{
				fishman[i]->SetPosition(camera->GetCameraPosition().x + rand() % 500, 500);
				if (fishman[i]->GetPosition().x + 34 < simon->GetPosition().x - 50)
				{
					fishman[i]->nx = 1;
					fishman[i]->SetState(FISH_MAN_STATE_JUMP);
					fishman[i]->SetEnable(true);
					fishman[i]->Respawn();
					watereffects[i]->SetEnable(fishman[i]->IsEnable());
					if (watereffects[i]->IsEnable())
					{
						watereffects[i]->SetVelocity();
						watereffects[i]->SetPosition(fishman[i]->GetPosition().x, fishman[i]->GetPosition().y + 30);
					}
				}
				if (fishman[i]->GetPosition().x > simon->GetPosition().x + 60 + 50)
				{
					fishman[i]->nx = -1;
					fishman[i]->SetState(FISH_MAN_STATE_JUMP);
					fishman[i]->SetEnable(true);
					fishman[i]->SetDamage(rand() % 4);
					if (fishman[i]->GetDamage() < 2)
						fishman[i]->SetDamage(2);
					fishman[i]->GetFireBall()->SetDamage(fishman[i]->GetDamage());
					fishman[i]->Respawn();
				}
			}
		}
		if (fishman[i]->GetFireBall()->GetPosition().x < camera->GetCameraPosition().x ||
			fishman[i]->GetFireBall()->GetPosition().x > camera->GetCameraPosition().x + SCREEN_WIDTH)
			fishman[i]->GetFireBall()->SetEnable(false);

	}
}
bool StateOne::IsInCamera(float x, float y)
{
	return (x > camera->GetCameraPosition().x
		&& x < camera->GetCameraPosition().x + SCREEN_WIDTH
		&& y > camera->GetCameraPosition().y
		&& y < camera->GetCameraPosition().y + SCREEN_HEIGHT);
}
void StateOne::UpdateWaterEffect(DWORD dt)
{
	for (int i = 0; i < 3; i++)
	{
		if (watereffects[i]->IsEnable())
			watereffects[i]->Update(dt);
	}
}
void StateOne::DestroyAll()
{
}
bool StateOne::GetChangingState()
{
	return false;
}
void StateOne::SetChangingState(bool status)
{
}


