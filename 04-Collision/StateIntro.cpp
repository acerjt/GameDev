#include "StateIntro.h"



StateIntro::StateIntro()
{
	camera = new Camera(0, 0);
	scene = new Scenes();
	scene->SetPosition(0, 0);
	helicopter = new Helicopter();
	helicopter->SetPosition(520.0f, 130);
	batintro[0] = new BatIntro();
	batintro[0]->SetPosition(50.0f, 250);
	batintro[0]->SetState(BAT_INTRO_STATE_FLY_UP);
	batintro[1] = new BatIntro();
	batintro[1]->SetPosition(350.0f, 130);
	batintro[1]->SetState(BAT_INTRO_STATE_FLY_STRAIGHT);
	brick = new CBrick(SCREEN_WIDTH+BRICK_BBOX_WIDTH,BRICK_BBOX_HEIGHT,STATE_INTRO);
	brick->SetPosition(0, 400);
	listObject.push_back(brick);
	simon->SetPosition(SCREEN_WIDTH, 320);
	for (int i = 0; i < listObject.size(); i++)
	{
		coObjects.push_back(listObject[i]);
	}
}


StateIntro::~StateIntro()
{
}


void StateIntro::Update(DWORD dt)
{
	
	helicopter->Update(dt);
	batintro[0]->Update(dt);
	batintro[1]->Update(dt);
	

	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Update(dt, &coObjects);
	}

	if (simon->x > SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH/2)
	{
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	}
	simon->Update(dt, &coObjects);
	if (simon->x < SCREEN_WIDTH / 2 - SIMON_BBOX_WIDTH/2)
	{
		simon->SetPosition(simon->x, simon->y);
		simon->SetState(SIMON_STATE_IDLE_2);
		this->timeDelay += dt;
		if (this->timeDelay >= STATE_INTRO_LIVE_TIME)
		{
			SetChangingState(true);
			simon->SetState(SIMON_STATE_IDLE);
			simon->nx = 1;
		}
	}
}

void StateIntro::Render(Camera *camera)
{
	//camera = this->camera;
	scene->Render(camera);
	helicopter->Render(camera);
	batintro[0]->Render(camera);
	batintro[1]->Render(camera);
	simon->Render(camera);
	for (int i = 0; i < listObject.size(); i++)
	{
		listObject[i]->Render(camera);
	}
}
bool StateIntro::GetChangingState()
{
	return GameState::GetChangingState();
}
void StateIntro::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void StateIntro::DestroyAll()
{	
	//delete(simon);
	delete(camera);
	listObject.clear();
	coObjects.clear();
	delete(helicopter);
	delete(scene);
	for(int i = 0; i < 2;i++)
		delete(batintro[i]);

}