#include "Scenes.h"
#include "StateManager.h"

void Scenes::Render(Camera *camera)
{
	CSprites * sprites = CSprites::GetInstance();
	switch (StateManager::stateID)
	{
	case -2:
		sprite = sprites->Get(1001);
		break;
	case -1:
		sprite = sprites->Get(1002);
		break;
	}
	sprite->Draw(camera, x, y);
}



void Scenes::GetBoundingBox(float &l, float &t, float &r, float &b)
{

}


Scenes::Scenes():CGameObject()
{
	
}


Scenes::~Scenes()
{
}
