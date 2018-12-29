#include "Brick.h"
#include "Game.h"
#include "StateManager.h"

void CBrick::Render(Camera *camera)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(x,y,0);
	CSprites * sprites = CSprites::GetInstance();
	switch (StateManager::stateID) {
		case STATE_INTRO:
			sprite = sprites->Get(ID_TEX_TRANSPARENT);
			break;
		case STATE_OUT_CASTLE:
			sprite = sprites->Get(5001);
			break;
		case STATE_ONE:
			sprite = sprites->Get(5002);
			break;
	}
	for (int j = 0; j < height / 32; j++)
	{
		pos.y = y + 32 * j;
		for (int i = 0; i < width / 32; i++)
		{
			pos.x = x + 32 * i;
			if(isEnable)
			sprite->Draw(camera,pos);
		}
	}
	//RenderBoundingBox(camera);
}
void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

CBrick::CBrick()
{

}
