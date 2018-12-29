#include "GameState.h"
#include "Game.h"
Simon* GameState::simon = NULL;
bool GameState::changeState = false;

void GameState::Update(DWORD dt)
{
	if (Simon::IsKillAll())
	{
		for (int i = 0; i < listEnemy.size(); i++)
		{
			listEnemy[i]->SetHP(0);
		}
		timeKillAll += dt;
		if (timeKillAll < 400)
		{
			if ((int)(timeKillAll) % 2 == 0)
				CGame::SetColor(D3DCOLOR_XRGB(255, 255, 255));
			else
				CGame::SetColor(D3DCOLOR_XRGB(0, 0, 0));
		}
		else
		{
			CGame::SetColor(D3DCOLOR_XRGB(0, 0, 0));
			Simon::SetIsKillAll(false);
			choose = false;
			timeKillAll = 0;
		}
	}
}
