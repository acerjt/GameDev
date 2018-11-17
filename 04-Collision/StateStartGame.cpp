#include "StateStartGame.h"



StateStartGame::StateStartGame()
{
	changeState = false;
	camera = new Camera(0, 0);
	scene = new Scenes();
	scene->SetPosition(0, 0);
	bat_st = new Batstartgame();
	bat_st->SetPosition(366.0f, 194);
	simon = new Simon();
}


StateStartGame::~StateStartGame()
{
}
void StateStartGame::Render(Camera *camera)
{
	scene->Render(camera);
	bat_st->Render(camera);
}

void StateStartGame::Update(DWORD dt)
{
	if (GetChangingState()==true)
	{
		scene->changescene += 1;
	}
}
bool StateStartGame::GetChangingState()
{
	return GameState::GetChangingState();
}
void StateStartGame::SetChangingState(bool status)
{
	GameState::SetChangingState(status);
}

void StateStartGame::DestroyAll() {}


