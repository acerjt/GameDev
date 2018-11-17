#include "StateManager.h"



StateManager::StateManager()
{
	
	stateID = STATE_START_GAME;
}


StateManager::~StateManager()
{
}
Simon* StateManager::simon = NULL;
void StateManager::LoadState(int stateID,Simon *simon)
{


	switch (stateID)
	{
	case STATE_START_GAME:
		gameState = new StateStartGame();
		gameState->simon = simon;
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_INTRO:
		gameState = new StateIntro();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_OUT_CASTLE:
		delete(gameState);
		gameState = new StateOutCastle();
		gameState->simon = simon;
		Item::TakeSimonPointer(simon);
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	//case GAME_PLAY_STATE_TWO:
	//	delete(gameState);
	//	gameState = new GamePlayStateTwo();
	//	if (!gameState->Initialize(gDevice))
	//		return;
	//	gameState->state = stateID;
	//	this->stateID = stateID;
	//	break;
	//case GAME_PLAY_STATE_THREE:
	//	delete(gameState);
	//	gameState = new GamePlayStateThree();
	//	if (!gameState->Initialize(gDevice))
	//		return;
	//	gameState->state = stateID;
	//	this->stateID = stateID;
	//	break;
	default:
		break;
	}
}

void StateManager::NextStateLevel()
{
	stateID++;
}

void StateManager::Render(Camera *camera)
{
	

	gameState->Render(camera);


}

void StateManager::Update(DWORD dt)
{

	gameState->Update(dt);
	if (gameState->GetChangingState())
	{
		if (stateID != STATE_START_GAME)
		{
			gameState->DestroyAll();
		}
		NextStateLevel();
		LoadState(stateID,gameState->simon);
		gameState->SetChangingState(false);
	}

	
}

