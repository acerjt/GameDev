#include "StateManager.h"



StateManager::StateManager()
{
	
	stateID = STATE_START_GAME;
}


StateManager::~StateManager()
{
}
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
		delete(gameState);
		gameState = new StateIntro();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_OUT_CASTLE:
		delete(gameState);
		gameState = new StateOutCastle();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	case STATE_ONE:
		delete(gameState);
		gameState = new StateOne();
		gameState->state = stateID;
		this->stateID = stateID;
		break;
	
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
		NextStateLevel();
		LoadState(stateID,gameState->simon);
		gameState->SetChangingState(false);
	}
}

